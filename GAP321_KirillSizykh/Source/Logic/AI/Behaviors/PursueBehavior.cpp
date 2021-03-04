#include "PursueBehavior.h"
#include <Logic/Actor/Actor.h>
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/Kinematic/KinematicComponent.h>
#include <Utils/Logger.h>
#include <cassert>

PursueBehavior::PursueBehavior()
    :ArriveBehavior()
    ,m_pTargetActorKinematicData(nullptr)
    ,m_pTargetActorTransform(nullptr)
    ,m_predictionTime(1.f)
{
}

void PursueBehavior::Update(float deltaSeconds)
{
    UpdateTarget();
    ArriveBehavior::Update(deltaSeconds);
}

bool PursueBehavior::SetTargetActor(yang::Actor* pActor)
{
    assert(pActor);
    
    m_pTargetActorTransform = pActor->GetComponent<yang::TransformComponent>();

    if (!m_pTargetActorTransform)
    {
        LOG(Error, "Target doesn't have transform component");
        return false;
    }

    m_pTargetActorKinematicData = pActor->GetComponent<yang::KinematicComponent>();
    if (!m_pTargetActorKinematicData)
    {
        LOG(Error, "Target doesn't have kinematic component");
        return false;
    }

    return true;
}

void PursueBehavior::UpdateTarget()
{
    m_target = m_pTargetActorTransform->GetPosition() + m_pTargetActorKinematicData->GetVelocity() * m_predictionTime;
}
