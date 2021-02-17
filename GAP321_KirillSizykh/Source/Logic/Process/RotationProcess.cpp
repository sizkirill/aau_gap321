#include "RotationProcess.h"

#include <Logic/Actor/Actor.h>
#include <cassert>

using yang::Vector2;
using yang::IProcess;

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::shared_ptr<IProcess> IProcess::CreateProcess<RotationProcessDescription::GetHashName()>(std::shared_ptr<yang::Actor> pOwner)
{
    return std::make_shared<RotationProcess>(pOwner);
};

#pragma warning(pop)

void RotationProcessDescription::Update(float deltaSeconds, yang::TransformComponent* pTransformComponent, yang::RotationComponent* pRotationComponent)
{
    assert(pTransformComponent);
    assert(pRotationComponent);

    auto speed = pRotationComponent->GetRotationSpeed();
    auto acceleration = pRotationComponent->GetAcceleration();

    pRotationComponent->SetRotationSpeed(speed + acceleration * deltaSeconds);
    
    pTransformComponent->Rotate(speed * deltaSeconds);
}

bool RotationProcessDescription::Init(tinyxml2::XMLElement* pData)
{
    return true;
}

bool RotationProcessDescription::PostInit(yang::TransformComponent* pTransformComponent, yang::RotationComponent* pRotationComponent)
{
    return true;
}
