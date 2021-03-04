#include "ArriveBehavior.h"
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/Kinematic/KinematicComponent.h>
#include <cassert>

ArriveBehavior::ArriveBehavior()
    :TargetedSteeringBehavior()
    ,m_targetRadius(1.f)
    ,m_slowRadius(10.f)
    ,m_timeToTarget(0.1f)
{
}

void ArriveBehavior::Update(float deltaSeconds)
{
    assert(m_pAgentKinematicData);
    assert(m_pAgentTransform);

    yang::FVec2 delta = m_target - m_pAgentTransform->GetPosition();
    float distanceSqrd = delta.SqrdLength();

    if (distanceSqrd < m_targetRadius * m_targetRadius)
    {
        m_pAgentKinematicData->Stop();
        return;
    }

    float desiredSpeed = m_pAgentKinematicData->GetMaxSpeed();

    if (distanceSqrd < m_slowRadius * m_slowRadius)
    {
        desiredSpeed = desiredSpeed * sqrt(distanceSqrd) / m_slowRadius;
    }

    yang::FVec2 targetVelocity = delta;
    targetVelocity.Normalize();
    targetVelocity *= desiredSpeed;

    yang::FVec2 targetAcceleration = targetVelocity - m_pAgentKinematicData->GetVelocity();
    targetAcceleration /= m_timeToTarget;

    m_pAgentKinematicData->Accelerate(deltaSeconds, targetAcceleration, 0);
    m_pAgentKinematicData->SetOrientationFromVelocity();
}

