#include "GraphSearcher.h"
#include <Utils/Logger.h>
#include <Logic/Map/BasicPathfindingMap.h>
#include <Logic/Event/EventDispatcher.h>
#include <Logic/Event/ReceivePathEvent.h>
#include <cassert>
#include <algorithm>

static constexpr float kSqrt2 = Math::Sqrt(2.f);

GraphSearcher::GraphSearcher(std::shared_ptr<BasicPathfindingMap> pMap)
    :m_pMap(pMap)
    ,m_pathRequestQueue()
{
    m_requestPathListener.Register([this](yang::IEvent* pEvent) {HandleRequestPathEvent(pEvent); });
}

GraphSearcher::~GraphSearcher()
{
    m_pathRequestQueue.clear();
}

void GraphSearcher::ProcessRequests()
{
    if (m_pathRequestQueue.empty())
    {
        return;
    }

    using namespace std::chrono;

    float timeLeft = kMaxTimeToUpdate;
    time_point<steady_clock> requestStart;
    time_point<steady_clock> requestEnd = steady_clock::now();

    while (!m_pathRequestQueue.empty())
    {
        requestStart = steady_clock::now();
        timeLeft -= duration<float>(requestEnd - requestStart).count();
        if (timeLeft < 0)
        {
            return;
        }

        PathRequest& request = *m_pathRequestQueue.begin();
        ProcessRequest(timeLeft);

        // TODO: handle the pathfinding failure
        if (request.m_status == PathRequest::Status::kFinished || request.m_status == PathRequest::Status::kFailed)
        {
            std::pop_heap(m_pathRequestQueue.begin(), m_pathRequestQueue.end(), PathRequest::Compare);
            m_pathRequestQueue.pop_back();
        }
        else
        {
            return;
        }

        requestEnd = steady_clock::now();
    }

}

void GraphSearcher::HandleRequestPathEvent(yang::IEvent* pEvent)
{
    using namespace yang;

    assert(RequestPathEvent::kEventId == pEvent->GetEventId());

    RequestPathEvent* pResult = static_cast<RequestPathEvent*>(pEvent);

    m_pathRequestQueue.emplace_back(pResult->actorId, pResult->pathStart, pResult->pathEnd);
    std::push_heap(m_pathRequestQueue.begin(), m_pathRequestQueue.end(), PathRequest::Compare);
}

void GraphSearcher::ProcessRequest(float maxTime)
{
    using namespace std::chrono;
    time_point<steady_clock> requestStart = steady_clock::now();

    // if we're here - we have something to proceed.. consider changing to if in case it won't be always true
    assert(m_pathRequestQueue.size() > 0);

    // We're always processing the request that is on top of the heap, so index [0]
    PathRequest& request = m_pathRequestQueue[0];

    auto pMap = m_pMap.lock();
    if (!pMap)
        return;

    auto endTileIndex = pMap->GetTileIndexFromWorldPoint(request.m_end);

    // Heuristic function. Diagonal distance between 2 points. Better than (end-start).Length(). Not as good as manhattan distance, but manhattan distance might give the wrong result
    auto heuristicFunc = [this, endTileIndex, pMap](size_t startIndex)
    {
        auto firstCoords = pMap->GetCoordsFromIndex(startIndex);
        auto secondCoords = pMap->GetCoordsFromIndex(endTileIndex);

        auto distanceVec = yang::IVec2(secondCoords) - yang::IVec2(firstCoords);

        int dx = std::abs(distanceVec.x);
        int dy = std::abs(distanceVec.y);

        return (dx + dy + (kSqrt2 - 2) * std::min(dx, dy));
    };

    time_point<steady_clock> requestUpdate = steady_clock::now();

    if (request.m_status == PathRequest::Status::kWaiting)
    {
        if (request.m_printDebugInfo)
        {
            pMap->ResetDebugInfo();
        }

        auto firstTileIndex = pMap->GetTileIndexFromWorldPoint(request.m_start);

        PathPlanNode startNode(firstTileIndex, 0.f, heuristicFunc(firstTileIndex), nullptr);
        request.m_nodes.emplace(std::make_pair(firstTileIndex, std::move(startNode)));

        request.m_openSet.emplace(&request.m_nodes.find(firstTileIndex)->second);
        request.m_status = PathRequest::Status::kProcessing;
        
        if (request.m_printDebugInfo)
        {
            pMap->SetDebugValue(firstTileIndex, BasicPathfindingMap::DebugValue::kOpenSet);
        }

        requestUpdate = steady_clock::now();
        float timeSinceStart = duration<float>(requestUpdate - requestStart).count();
        maxTime -= timeSinceStart;

        if (maxTime < 0)
        {
            if (request.m_printDebugInfo)
            {
                LOG("Pathfinding", "Processed path request for %f seconds. Path request not finished", timeSinceStart);
            }
            return;
        }
    }
    
    if (request.m_status == PathRequest::Status::kProcessing)
    {
        while (!request.m_openSet.empty())
        {
            float timeSinceLast = duration<float>(steady_clock::now() - requestUpdate).count();
            requestUpdate = steady_clock::now();
            maxTime -= timeSinceLast;

            if (maxTime < 0)
            {
                if (request.m_printDebugInfo)
                {
                    float timeSinceStart = duration<float>(steady_clock::now() - requestStart).count();
                    LOG("Pathfinding", "Processed path request for %f seconds. Path request not finished", timeSinceStart);
                }
                return;
            }

            PathPlanNode* pCurrentNode = *request.m_openSet.begin();

            request.m_openSet.erase(request.m_openSet.begin());

            pCurrentNode->m_isClosed = true;

            if (request.m_printDebugInfo)
            {
                pMap->SetDebugValue(pCurrentNode->m_tileIndex, BasicPathfindingMap::DebugValue::kClosedSet);
            }

            if (pCurrentNode->m_tileIndex == endTileIndex)
            {
                if (request.m_printDebugInfo)
                {
                    float timeSinceStart = duration<float>(steady_clock::now() - requestStart).count();
                    LOG("Pathfinding", "Processed path request for %f seconds. Path request finished", timeSinceStart);
                }

                yang::EventDispatcher::Get()->QueueEvent(std::make_unique<ReceivePathEvent>(ReconstructPath(pCurrentNode), request.m_actorId));
                request.m_status = PathRequest::Status::kFinished;

                return;
            }

            // Well, here we can't interrupt the process, so all neighbors will be processed. Or I guess you can, but a lot of work just for that
            for (auto& neighbor : pMap->GetNeighbors(pCurrentNode->m_tileIndex))
            {
                // Neighbor might not be there
                if (!neighbor)
                {
                    continue;
                }

                auto containsIt = request.m_nodes.find(neighbor->first);

                float tentativeScore = pCurrentNode->m_currentWeight + neighbor->second;

                // If node is in the closed set - continuing to the next neighbor
                if (containsIt != request.m_nodes.end() && containsIt->second.m_isClosed)
                {
                    continue;
                }

                // if we already have that node expanded a while ago, find it and reinsert in the open set
                if (containsIt != request.m_nodes.end() && tentativeScore < containsIt->second.m_currentWeight)
                {
                    containsIt->second.m_pPrev = pCurrentNode;
                    containsIt->second.m_currentWeight = tentativeScore;

                    auto [startIt, endIt] = request.m_openSet.equal_range(&containsIt->second);
                    while (startIt != endIt)
                    {
                        // if open set contains it already - reinsert it
                        if (&containsIt->second == *startIt)
                        {
                            // Have to reinsert the value. O(2 * log n)
                            auto node = request.m_openSet.extract(startIt);
                            request.m_openSet.insert(std::move(node));
                            break;
                        }
                        ++startIt;

                        // if open set doesn't have it - just insert it
                        if (startIt == endIt)
                        {
                            request.m_openSet.insert(&containsIt->second);
                        }
                    }

                    if (request.m_printDebugInfo)
                    {
                        pMap->SetDebugValue(containsIt->second.m_tileIndex, BasicPathfindingMap::DebugValue::kOpenSet);
                    }
                }
                // if it is a new node, construct a path plan node for it and insert in the open set
                else if (containsIt == request.m_nodes.end())
                {
                    PathPlanNode toAdd = PathPlanNode(neighbor->first, tentativeScore, heuristicFunc(neighbor->first), pCurrentNode);

                    auto elem = request.m_nodes.emplace(std::make_pair(neighbor->first, std::move(toAdd)));

                    request.m_openSet.emplace(&elem.first->second);
                    
                    if (request.m_printDebugInfo)
                    {
                        pMap->SetDebugValue(elem.first->second.m_tileIndex, BasicPathfindingMap::DebugValue::kOpenSet);
                    }
                }
            }
        }

        if (request.m_printDebugInfo)
        {
            float timeSinceStart = duration<float>(steady_clock::now() - requestStart).count();
            LOG("Pathfinding", "Processed path request for %f seconds. Path request failed", timeSinceStart);
        }
        // We're screwed
        request.m_status = PathRequest::Status::kFailed;
    }
}

Path GraphSearcher::ReconstructPath(PathPlanNode* pEnd)
{
    // filling up the path stack
    Path path;
    assert(pEnd);

    auto pMap = m_pMap.lock();
    assert(pMap);

    assert(m_pathRequestQueue.size() > 0);

    while (pEnd != nullptr)
    {
        if (m_pathRequestQueue[0].m_printDebugInfo)
        {
            pMap->SetDebugValue(pEnd->m_tileIndex, BasicPathfindingMap::DebugValue::kPath);
        }
        path.emplace(std::move(pMap->GetWorldPointFromTileIndex(pEnd->m_tileIndex)));
        pEnd = pEnd->m_pPrev;
    }
    return path;
}

PathRequest::PathRequest(uint32_t actorId, yang::FVec2 start, yang::FVec2 end, bool printDebugInfo, size_t priority)
    :m_actorId(actorId)
    ,m_start(start)
    ,m_end(end)
    ,m_priority(priority)
    ,m_status(Status::kWaiting)
    ,m_printDebugInfo(printDebugInfo)
    ,m_openSet(&PathPlanNode::Compare)
{
}