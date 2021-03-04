#include "MoveComponent.h"
#include <Utils/Logger.h>
#include <Utils/TinyXml2/tinyxml2.h>
#include <Logic/Actor/Actor.h>
#include <Logic/Components/TransformComponent.h>
#include <cassert>

#include <Logic/Scripting/LuaManager.h>

using yang::MoveComponent;
using yang::IComponent;

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::unique_ptr<IComponent> yang::IComponent::CreateComponent<StringHash32(MoveComponent::GetName())>(Actor* pOwner) { return std::make_unique<MoveComponent>(pOwner); };

#pragma warning(pop)

MoveComponent::MoveComponent(yang::Actor* pOwner)
    :IComponent(pOwner, GetName())
    ,m_acceleration(0)
    ,m_maxAcceleration(0)
    ,m_speed(0)
    ,m_velocityDirection(FVec2(0,0))
    ,m_accelerationDirection(FVec2(0,0))
    ,m_maxSpeed(0)
{
	
}

bool yang::MoveComponent::Init(tinyxml2::XMLElement* pData)
{
    using namespace tinyxml2;

    m_maxSpeed = pData->FloatAttribute("maxSpeed");
    m_speed = pData->FloatAttribute("speed");
    m_speed = std::clamp(m_speed, 0.f, m_maxSpeed);
    
    m_maxAcceleration = pData->FloatAttribute("maxAcceleration");
    m_acceleration = pData->FloatAttribute("acceleration");
    m_acceleration = std::clamp(m_acceleration, 0.f, m_maxAcceleration);

    XMLElement* pVelocity = pData->FirstChildElement("Velocity");
    if (pVelocity)
    {
        m_velocityDirection.x = pVelocity->FloatAttribute("x");
        m_velocityDirection.y = pVelocity->FloatAttribute("y");
        m_velocityDirection.Normalize();
    }

    XMLElement* pAcceleration = pData->FirstChildElement("Acceleration");
    if (pAcceleration)
    {
        m_accelerationDirection.x = pAcceleration->FloatAttribute("x");
        m_accelerationDirection.y = pAcceleration->FloatAttribute("y");
        m_accelerationDirection.Normalize();
    }

    return true;
}

#ifdef DEBUG_PANEL
void yang::MoveComponent::AttachToDebugPanel(DebugPanel& panel, DebugPanel::ActorSection& actorSection) const
{
    auto& componentSection = panel.AddSection(GetName(), actorSection);
    panel.AttachToDebugPanel(componentSection, "Speed", [this]() {return std::to_string(m_speed); });
    panel.AttachToDebugPanel(componentSection, "Acceleration", [this]() {return std::to_string(m_acceleration); });
    panel.AttachToDebugPanel(componentSection, "Velocity dir", [this]() {return "x: " + std::to_string(m_velocityDirection.x) + "; y: " + std::to_string(m_velocityDirection.y); });
    panel.AttachToDebugPanel(componentSection, "Acceleration dir", [this]() {return "x: " + std::to_string(m_accelerationDirection.x) + "; y: " + std::to_string(m_accelerationDirection.y); });
}
#endif

void yang::MoveComponent::SetSpeed(float speed)
{
    m_speed = std::clamp(speed, 0.f, m_maxSpeed);
}

void yang::MoveComponent::SetVelocityDirection(FVec2 velocityDirection)
{
    m_velocityDirection = FVec2::Normalized(velocityDirection);
}

void yang::MoveComponent::SetAccelerationDirection(FVec2 accelerationDirection)
{
    m_accelerationDirection = FVec2::Normalized(accelerationDirection);
}

void yang::MoveComponent::SetAcceleration(float acceleration)
{
    m_acceleration = std::clamp(acceleration, 0.f, m_maxAcceleration);
}
