#include "MoveProcess.h"

#include <Logic/Actor/Actor.h>
#include <cassert>

using yang::Vector2;
using yang::IProcess;

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::shared_ptr<IProcess> IProcess::CreateProcess<MoveProcessDescription::GetHashName()>(std::shared_ptr<yang::Actor> pOwner)
{
    return std::make_shared<MoveProcess>(pOwner);
};

#pragma warning(pop)

void MoveProcessDescription::Update(float deltaSeconds, yang::TransformComponent* pTransformComponent, yang::MoveComponent* pMoveComponent)
{
    assert(pTransformComponent);
    assert(pMoveComponent);

    auto actualAcceleration = pMoveComponent->GetAcceleration() * pMoveComponent->GetAccelerationDirection();
    auto actualVelocity = pMoveComponent->GetVelocityDirection() * pMoveComponent->GetSpeed();

    auto desiredVelocity = actualVelocity + actualAcceleration * deltaSeconds;
    pMoveComponent->SetSpeed(desiredVelocity.Length());
    pMoveComponent->SetVelocityDirection(desiredVelocity);

    pTransformComponent->Move(actualVelocity * deltaSeconds);
}

bool MoveProcessDescription::Init(tinyxml2::XMLElement* pData)
{
    return true;
}

bool MoveProcessDescription::PostInit(yang::TransformComponent* pTransformComponent, yang::MoveComponent* pMoveComponent)
{
    return true;
}
