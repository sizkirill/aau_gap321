#pragma once

#include "SteeringBehavior.h"
#include <Utils/Vector2.h>

class TargetedSteeringBehavior : public SteeringBehavior
{
public:
    TargetedSteeringBehavior();
   
protected:
    yang::FVec2 m_target;
    
public:
    void SetTarget(yang::FVec2 target) { m_target = target; }
    yang::FVec2 GetTarget() const { return m_target; }
    
};