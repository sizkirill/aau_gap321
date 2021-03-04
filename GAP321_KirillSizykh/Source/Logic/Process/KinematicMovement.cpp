#include "KinematicMovement.h"

#include <Logic/Actor/Actor.h>
#include <cassert>

using yang::Vector2;
using yang::IProcess;

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::shared_ptr<IProcess> IProcess::CreateProcess<KinematicMovementDescription::GetHashName()>(std::shared_ptr<yang::Actor> pOwner)
{
    return std::make_shared<KinematicMovement>(pOwner);
};

#pragma warning(pop)

void KinematicMovementDescription::Update(float deltaSeconds, yang::TransformComponent* pTransformComponent, yang::KinematicComponent* pKinematicComponent)
{
    assert(pTransformComponent);
    assert(pKinematicComponent);

    pTransformComponent->Move(pKinematicComponent->GetVelocity() * deltaSeconds);
    pTransformComponent->Rotate(pKinematicComponent->GetAngularVelocity() * deltaSeconds);
    pKinematicComponent->Accelerate(deltaSeconds, pKinematicComponent->GetAcceleration(), pKinematicComponent->GetAngularAcceleration());
}

bool KinematicMovementDescription::Init(tinyxml2::XMLElement* pData)
{
    return true;
}

bool KinematicMovementDescription::PostInit(yang::TransformComponent* pTransformComponent, yang::KinematicComponent* pKinematicComponent)
{
    return true;
}
