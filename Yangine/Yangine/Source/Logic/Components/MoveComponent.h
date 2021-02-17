#pragma once
/** \file MoveComponent.h */
/** MoveComponent description */

#include ".\IComponent.h"
#include <Utils/Math.h>
#include <Utils/Vector2.h>
#include <Utils/Typedefs.h>

//! \namespace yang Contains all Yangine code
namespace yang
{
	class LuaManager;
    class TransformComponent;
    class Actor;
/** \class MoveComponent */
/** Actor component that stores data for the actor movement */
class MoveComponent
	: public IComponent
{
public:
    /// Constructor
    /// \param pOwner - actor, that owns this component
	MoveComponent(Actor* pOwner);

	/** Default Destructor */
    ~MoveComponent() = default;

    /// Initialize the component from an XML element
    /// \param pData - XML Element that contains component data
    /// \return true if initialized successfully
    virtual bool Init(tinyxml2::XMLElement* pData) override final;

    // TODO: make this not a virtual function, so it will be called only where it should be called. Right now it is unusable.
    /// Updates this component by deltaSeconds time
    /// \param deltaSeconds - number of seconds since last frame
    //virtual void Update(float deltaSeconds) override final;

    /// Name of this component, used for hashing
    /// \return "MoveComponent"
    static constexpr const char* GetName() { return "MoveComponent"; }

private:
    float m_maxSpeed;
    float m_maxAcceleration;

    float m_acceleration;
    float m_speed;

    FVec2 m_velocityDirection;
    FVec2 m_accelerationDirection;

public:
    float GetMaxSpeed() const { return m_maxSpeed; }
    float GetMaxAcceleration() const { return m_maxAcceleration; }

    float GetAcceleration() const { return m_acceleration; }
    float GetSpeed() const { return m_speed; }

    void SetSpeed(float speed);
    void SetAcceleration(float acceleration);

    FVec2 GetVelocityDirection() const { return m_velocityDirection; }
    FVec2 GetAccelerationDirection() const { return m_accelerationDirection; }

    void SetVelocityDirection(FVec2 velocityDirection);
    void SetAccelerationDirection(FVec2 accelerationDirection);
};
}