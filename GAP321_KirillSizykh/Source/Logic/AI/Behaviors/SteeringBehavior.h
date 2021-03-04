#pragma once

namespace yang
{
    class TransformComponent;
    class KinematicComponent;
}

namespace yang
{
    class Actor;
}

class SteeringBehavior
{
public:
    SteeringBehavior() = default;
    virtual bool Init(yang::Actor* pAgent);
    virtual void Update(float deltaSeconds) = 0;
protected:
    yang::TransformComponent* m_pAgentTransform;
    yang::KinematicComponent* m_pAgentKinematicData;
};