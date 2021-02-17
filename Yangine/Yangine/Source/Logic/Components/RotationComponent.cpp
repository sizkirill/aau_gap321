#include "RotationComponent.h"
#include <Utils/TinyXml2/tinyxml2.h>
#include <Logic/Actor/Actor.h>
#include <Logic/Components/TransformComponent.h>
#include <Utils/Math.h>

using yang::RotationComponent;
using yang::IComponent;

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::unique_ptr<IComponent> yang::IComponent::CreateComponent<StringHash32(RotationComponent::GetName())>(Actor* pOwner) { return std::make_unique<RotationComponent>(pOwner); };

#pragma warning(pop)

RotationComponent::RotationComponent(yang::Actor* pOwner)
	:IComponent(pOwner, GetName())
    ,m_rotationPoint(FVec2(0.f,0.f))
    ,m_rotationSpeed(0.f)
    ,m_acceleration(0.f)
    ,m_maxAcceleration(0.f)
{
	
}

bool yang::RotationComponent::Init(tinyxml2::XMLElement* pData)
{
    using namespace tinyxml2;

    m_maxRotationSpeed = Math::ToRadians(pData->FloatAttribute("maxSpeed"));
    m_maxAcceleration = Math::ToRadians(pData->FloatAttribute("maxAcceleration"));
    m_rotationSpeed = Math::ToRadians(pData->FloatAttribute("speed"));
    m_acceleration = Math::ToRadians(pData->FloatAttribute("acceleration"));

    XMLElement* pRotationPoint = pData->FirstChildElement("RotationPoint");
    if (pRotationPoint)
    {
        m_rotationPoint.x = pRotationPoint->FloatAttribute("x");
        m_rotationPoint.y = pRotationPoint->FloatAttribute("y");
    }

    return true;
}

void yang::RotationComponent::SetRotationSpeed(float radiansPerSec)
{
    m_rotationSpeed = std::clamp(radiansPerSec, -m_maxRotationSpeed, m_maxRotationSpeed);
}

void yang::RotationComponent::SetAcceleration(float acceleration)
{
    m_acceleration = std::clamp(acceleration, -m_maxAcceleration, m_maxAcceleration);
}
