#pragma once
#include "TargetedSteeringBehavior.h"

class SeekFleeBehavior : public TargetedSteeringBehavior
{
public:
    SeekFleeBehavior();
    virtual void Update(float deltaSeconds) override final;
    virtual yang::FVec2 GetInitialDirection() = 0;
private:

};

class SeekBehavior : public SeekFleeBehavior
{
public:
    SeekBehavior();
    virtual yang::FVec2 GetInitialDirection() override final;
};

class FleeBehavior : public SeekFleeBehavior
{
public:
    FleeBehavior();
    virtual yang::FVec2 GetInitialDirection() override final;
};