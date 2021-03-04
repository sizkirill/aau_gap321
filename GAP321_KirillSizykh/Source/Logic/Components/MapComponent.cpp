#include "MapComponent.h"
#include <Utils/tinyxml2/tinyxml2.h>
#include <Utils/StringHash.h>
#include <Logic/Map/BasicPathfindingMap.h>

using yang::IComponent;

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::unique_ptr<yang::IComponent> yang::IComponent::CreateComponent<StringHash32(MapComponent::GetName())>(yang::Actor* pOwner) { return std::make_unique<MapComponent>(pOwner); };

#pragma warning(pop)

MapComponent::MapComponent(yang::Actor* pOwner)
    :IComponent(pOwner, GetName())
{
	
}

bool MapComponent::Init(tinyxml2::XMLElement* pData)
{
    using namespace tinyxml2;

    // ofc it should be done better, but whatever
    m_pMap = std::make_unique<BasicPathfindingMap>();
    m_pGraphSearcher = std::make_unique<GraphSearcher>(m_pMap);

    if (auto pMapElement = pData->FirstChildElement("Map"); pMapElement != nullptr)
    {
        if (auto pathToMap = pMapElement->Attribute("src"); pathToMap != nullptr)
        {
            return m_pMap->LoadMap(pathToMap);
        }
    }

    return true;
}

bool MapComponent::Render(yang::IGraphics* pGraphics)
{
    return m_pMap->Render(pGraphics);
}

void MapComponent::Update(float deltaSeconds)
{
    m_pGraphSearcher->ProcessRequests();
}
