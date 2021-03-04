#include "AgentComponent.h"
#include <Utils/StringHash.h>
#include <Logic/AI/Behaviors/SeekFleeBehavior.h>
#include <Logic/AI/Behaviors/ArriveBehavior.h>
#include <Logic/Components/TransformComponent.h>
#include <Logic/Event/EventDispatcher.h>
#include <Logic/Event/Input/MouseButtonEvent.h>
#include <Logic/Event/RequestPathEvent.h>
#include <Logic/Actor/Actor.h>
#include <cassert>
#include <memory>

using yang::IComponent;

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::unique_ptr<IComponent> yang::IComponent::CreateComponent<StringHash32(AgentComponent::GetName())>(yang::Actor* pOwner) 
{ 
    return std::make_unique<AgentComponent>(pOwner); 
};

#pragma warning(pop)

AgentComponent::AgentComponent(yang::Actor* pOwner)
    :IComponent(pOwner, GetName())
    ,m_pAgentBehavior(nullptr)
    ,m_pTransform(nullptr)
    ,m_currentPath()
{
    m_mouseListener.Register([this](yang::IEvent* pEvent) {HandleClick(pEvent); });
    m_receivePathListener.Register([this](yang::IEvent* pEvent) {ReceivePath(pEvent); });
}

AgentComponent::~AgentComponent()
{
    if (m_pAgentBehavior)
    {
        delete m_pAgentBehavior;
        m_pAgentBehavior = nullptr;
    }
}

bool AgentComponent::Init(tinyxml2::XMLElement* pData)
{
    return true;
}

bool AgentComponent::PostInit()
{
    m_pTransform = GetOwner()->GetComponent<yang::TransformComponent>();

    assert(m_pTransform);

    m_pAgentBehavior = new ArriveBehavior();
    m_pAgentBehavior->Init(GetOwner());
    static_cast<TargetedSteeringBehavior*>(m_pAgentBehavior)->SetTarget(m_pTransform->GetPosition());

    return true;
}

void AgentComponent::Update(float deltaSeconds)
{
    if (!m_currentPath.empty())
    {
        yang::FVec2 currentTarget = m_currentPath.top();
        float distanceToNext = (currentTarget - m_pTransform->GetPosition()).SqrdLength();
        if (Math::IsExtremelyClose(distanceToNext, 0.f, 32.f))
        {
            m_currentPath.pop();
        }
        static_cast<TargetedSteeringBehavior*>(m_pAgentBehavior)->SetTarget(currentTarget); 
    }
    m_pAgentBehavior->Update(deltaSeconds);
}

void AgentComponent::HandleClick(yang::IEvent* pEvent)
{
    using namespace yang;

    assert(MouseButtonEvent::kEventId == pEvent->GetEventId());

    MouseButtonEvent* pResult = static_cast<MouseButtonEvent*>(pEvent);

    if (pResult->GetEventType() == MouseButtonEvent::EventType::kButtonPressed)
    {
        yang::EventDispatcher::Get()->QueueEvent(std::make_unique<RequestPathEvent>(m_pTransform->GetPosition(), pResult->GetClickPosition(), GetOwner()->GetId()));
        
        if (m_pAgentBehavior)
        {
            static_cast<TargetedSteeringBehavior*>(m_pAgentBehavior)->SetTarget(m_pTransform->GetPosition());
        }
    }
}

void AgentComponent::ReceivePath(yang::IEvent* pEvent)
{
    using namespace yang;

    assert(ReceivePathEvent::kEventId == pEvent->GetEventId());

    auto pResult = static_cast<ReceivePathEvent*>(pEvent);

    if (pResult->actorId == GetOwner()->GetId())
    {
        m_currentPath = std::move(pResult->path);
    }
}
