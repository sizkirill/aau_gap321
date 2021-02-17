#pragma once
/** \file RotationComponent.h */
/** Component that handles data for actor's rotation */

#include <Utils/Vector2.h>
#include ".\IComponent.h"

//! \namespace yang Contains all Yangine code
namespace yang
{
	class TransformComponent;

/** \class RotationComponent */
/** Component that handles data for actor's rotation */
class RotationComponent
	: public IComponent
{
public:
	/// Constructor
	/// \param pOwner - actor, that owns this component
	RotationComponent(Actor* pOwner);

	/** Default Destructor */
	~RotationComponent() = default;

	/// Name of this component, used for hashing
	/// \return "RotationComponent"
	static constexpr const char* GetName() { return "RotationComponent"; }

	/// Initialize the component from an XML element
	/// \param pData - XML Element that contains component data
	/// \return true if initialized successfully
	virtual bool Init(tinyxml2::XMLElement* pData) override final;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //

	/// \bried Maximum rotation speed in radians/second.
	float m_maxRotationSpeed;

	/// \brief Maximum rotation acceleration
	float m_maxAcceleration;

	/// \brief Rotation speed in radians/second. Positive is clockwise, negative - counter clockwise
	float m_rotationSpeed;

	/// \brief Rotation acceleration
	float m_acceleration;

	/// \brief Point to rotate about
	FVec2 m_rotationPoint;
	
	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //

	/// \brief Getter for maximum rotation speed
	/// \return Maximum rotation speed
	float GetMaxRotationSpeed() const { return m_maxRotationSpeed; }

	float GetMaxAcceleration() const { return m_maxAcceleration; }

	/// \brief Getter for rotation speed
	/// \return Rotation speed
	float GetRotationSpeed() const { return m_rotationSpeed; }

	/// \brief Setter for rotation speed
	/// \param degreesPerSec - new rotation speed in radians per second.
	void SetRotationSpeed(float radiansPerSec);

	/// \brief Getter for rotation point
	/// \return const reference to a rotation point
	FVec2 GetRotationPoint() const { return m_rotationPoint; }

	/// \brief Setter for rotation point
	/// \param point - new point to rotate about
	void SetRotationPoint(FVec2 point) { m_rotationPoint = point; }

	/// \brief Get the current rotation acceleration
	/// \return angular acceleration
	float GetAcceleration() const { return m_acceleration; }

	/// \brief Set the acceleration
	/// \param acceleration - new acceleration
	void SetAcceleration(float acceleration);

};
}