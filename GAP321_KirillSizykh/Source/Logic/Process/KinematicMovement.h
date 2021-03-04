#pragma once
/** \file KinematicMovement.h */
/** Describes KinematicMovement process */

#include <Logic/Process/BaseProcess.h>
#include <Logic/Components/Kinematic/KinematicComponent.h>
#include <Logic/Components/TransformComponent.h>
#include <Utils/StringHash.h>
#include <string_view>

class KinematicMovementDescription
{
public:
	KinematicMovementDescription([[maybe_unused]] yang::IProcess* pOwner) {};
	void Update(float deltaSeconds, yang::TransformComponent* pTransformComponent, yang::KinematicComponent* pKinematicComponent);
	bool Init(tinyxml2::XMLElement* pData);
	bool PostInit(yang::TransformComponent* pTransformComponent, yang::KinematicComponent* pKinematicComponent);

	static constexpr std::string_view kName = "KinematicMovement";
	static constexpr uint32_t kHashName = StringHash32(kName.data());

	static constexpr std::string_view GetName() { return kName; }
	static constexpr uint32_t GetHashName() { return kHashName; }
};

using KinematicMovement = yang::BaseProcess<KinematicMovementDescription, yang::TransformComponent, yang::KinematicComponent>;