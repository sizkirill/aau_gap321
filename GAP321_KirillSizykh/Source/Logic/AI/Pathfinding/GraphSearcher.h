#pragma once
#include <Utils/Vector2.h>
#include <memory>
#include <stack>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <Logic/Event/RequestPathEvent.h>
#include <Logic/Event/EventListener.h>

namespace yang
{
    class IEvent;
}

class BasicPathfindingMap;
using Path = std::stack<yang::FVec2, std::vector<yang::FVec2>>;

struct PathPlanNode
{
    PathPlanNode(size_t index, float weight, float heuristics, PathPlanNode* pPrev)
        :m_tileIndex(index)
        , m_currentWeight(weight)
        , m_heuristicsValue(heuristics)
        , m_pPrev(pPrev)
        , m_isClosed(false)
    {}

    size_t m_tileIndex;         ///< Tile index
    float m_currentWeight;      ///< gScore
    float m_heuristicsValue;    ///< hScore
    PathPlanNode* m_pPrev;      ///< Parent node
    bool m_isClosed;            ///< Is it in the closed set?

    static bool Compare(const PathPlanNode* pFirst, const PathPlanNode* pSecond) { return (pFirst->m_currentWeight + pFirst->m_heuristicsValue) < (pSecond->m_currentWeight + pSecond->m_heuristicsValue); }
};

struct PathRequest
{
public:
    enum class Status
    {
        kWaiting,
        kProcessing,
        kFinished,
        kFailed,
        kInvalidStatus
    };

    PathRequest(uint32_t actorId, yang::FVec2 start, yang::FVec2 end, bool printDebugInfo = true, size_t priority = 1);
    PathRequest(PathRequest&& other) = default;
    PathRequest& operator=(PathRequest&& other) = default;

    static bool Compare(const PathRequest& first, const PathRequest& second) { return first.m_priority < second.m_priority; }

    using NodeMap = std::unordered_map<size_t, PathPlanNode>;
    using OpenSet = std::multiset<PathPlanNode*, decltype(&PathPlanNode::Compare)>;

    yang::FVec2 m_start;
    yang::FVec2 m_end;
    uint32_t m_actorId;

    Status m_status;
    bool m_printDebugInfo;
    size_t m_priority;
    NodeMap m_nodes;
    OpenSet m_openSet;
};

class GraphSearcher
{
public:
    static constexpr float kMaxTimeToUpdate = 0.005f;

    GraphSearcher(std::shared_ptr<BasicPathfindingMap> pMap);
    ~GraphSearcher();

    void ProcessRequests();
private:
    // simulating a heap, but with an ability to modify it
    using PathRequestQueue = std::vector<PathRequest>;

    std::weak_ptr<BasicPathfindingMap> m_pMap;                            ///< Map to find a path on
    yang::EventListener<RequestPathEvent> m_requestPathListener;                      ///< Event listener
    PathRequestQueue m_pathRequestQueue;                    ///< Priority queue for path requests

    void HandleRequestPathEvent(yang::IEvent* pEvent);
    void ProcessRequest(float maxTime);
    Path ReconstructPath(PathPlanNode* pEnd);
};
