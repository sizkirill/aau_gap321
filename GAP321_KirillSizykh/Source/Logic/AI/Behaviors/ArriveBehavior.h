#pragma once

#include "TargetedSteeringBehavior.h"

class ArriveBehavior : public TargetedSteeringBehavior
{
public:
    ArriveBehavior();
    virtual void Update(float deltaSeconds) override;
private:
    float m_targetRadius;
    float m_slowRadius;
    float m_timeToTarget;
};