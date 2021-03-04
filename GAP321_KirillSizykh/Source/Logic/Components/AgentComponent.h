#pragma once
#include <Logic/Components/IComponent.h>
#include <Logic/AI/Pathfinding/GraphSearcher.h>
#include <Logic/Event/EventListener.h>
#include <Logic/Event/Input/MouseButtonEvent.h>
#include <Logic/Event/ReceivePathEvent.h>

namespace yang
{
    class TransformComponent;
    class IEvent;
}

class BasicPathfindingMap;
class GraphSearcher;
class SteeringBehavior;

class AgentComponent : public yang::IComponent
{
public:
    AgentComponent(yang::Actor* pOwner);
    virtual ~AgentComponent() override final;

    static constexpr const char* GetName() { return "AgentComponent"; }

    virtual bool Init(tinyxml2::XMLElement* pData) override final;

    virtual bool PostInit() override final;

    virtual void Update(float deltaSeconds) override final;
private:
    SteeringBehavior* m_pAgentBehavior;
    yang::TransformComponent* m_pTransform;

    yang::EventListener<yang::MouseButtonEvent> m_mouseListener;
    yang::EventListener<ReceivePathEvent> m_receivePathListener;
    Path m_currentPath;

    void HandleClick(yang::IEvent* pEvent);
    void ReceivePath(yang::IEvent* pEvent);
};