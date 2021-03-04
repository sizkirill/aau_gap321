#pragma once
#include "ArriveBehavior.h"

class PursueBehavior : public ArriveBehavior
{
public:
    PursueBehavior();
    virtual void Update(float deltaSeconds) override final;
private:
    yang::TransformComponent* m_pTargetActorTransform;
    yang::KinematicComponent* m_pTargetActorKinematicData;
    float m_predictionTime;
public:
    bool SetTargetActor(yang::Actor* pActor);
    yang::TransformComponent* GetTargetTransform() const { return m_pTargetActorTransform; }
    yang::KinematicComponent* GetTargetKinematicData() const { return m_pTargetActorKinematicData; }

private:
    void UpdateTarget();
};
