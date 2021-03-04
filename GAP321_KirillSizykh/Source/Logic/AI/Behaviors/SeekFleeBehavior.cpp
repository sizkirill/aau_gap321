#include "SeekFleeBehavior.h"
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/Kinematic/KinematicComponent.h>
#include <cassert>

SeekFleeBehavior::SeekFleeBehavior()
    :TargetedSteeringBehavior()
{
}

void SeekFleeBehavior::Update(float deltaSeconds)
{
    assert(m_pAgentKinematicData);

    auto direction = GetInitialDirection();
    direction.Normalize();
    direction *= m_pAgentKinematicData->GetMaxAcceleration();

    m_pAgentKinematicData->Accelerate(deltaSeconds, direction, 0);
    m_pAgentKinematicData->SetOrientationFromVelocity();
}


SeekBehavior::SeekBehavior()
    :SeekFleeBehavior()
{
}

yang::FVec2 SeekBehavior::GetInitialDirection()
{
    assert(m_pAgentTransform);
    return m_target - m_pAgentTransform->GetPosition();
}

FleeBehavior::FleeBehavior()
    :SeekFleeBehavior()
{
}

yang::FVec2 FleeBehavior::GetInitialDirection()
{
    assert(m_pAgentTransform);
    return m_pAgentTransform->GetPosition() - m_target;
}
