#pragma once
/** \file RotationProcess.h */
/** Describes RotationProcess process */

#include <Logic/Process/BaseProcess.h>
#include <Logic/Components/RotationComponent.h>
#include <Logic/Components/TransformComponent.h>
#include <Utils/StringHash.h>
#include <string_view>

class RotationProcessDescription
{
public:
	RotationProcessDescription([[maybe_unused]] yang::IProcess* pOwner) {};
	void Update(float deltaSeconds, yang::TransformComponent* pTransformComponent, yang::RotationComponent* pRotationComponent);
	bool Init(tinyxml2::XMLElement* pData);
	bool PostInit(yang::TransformComponent* pTransformComponent, yang::RotationComponent* pRotationComponent);

	static constexpr std::string_view kName = "RotationProcess";
	static constexpr uint32_t kHashName = StringHash32(kName.data());

	static constexpr std::string_view GetName() { return kName; }
	static constexpr uint32_t GetHashName() { return kHashName; }
};

using RotationProcess = yang::BaseProcess<RotationProcessDescription, yang::TransformComponent, yang::RotationComponent>;