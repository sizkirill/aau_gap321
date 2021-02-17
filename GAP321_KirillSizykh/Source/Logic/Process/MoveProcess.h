#pragma once
/** \file MoveProcess.h */
/** Describes MoveProcess process */

#include <Logic/Process/BaseProcess.h>
#include <Logic/Components/MoveComponent.h>
#include <Logic/Components/TransformComponent.h>
#include <Utils/StringHash.h>
#include <string_view>

class MoveProcessDescription
{
public:
	MoveProcessDescription([[maybe_unused]] yang::IProcess* pOwner) {};
	void Update(float deltaSeconds, yang::TransformComponent* pTransformComponent, yang::MoveComponent* pMoveComponent);
	bool Init(tinyxml2::XMLElement* pData);
	bool PostInit(yang::TransformComponent* pTransformComponent, yang::MoveComponent* pMoveComponent);

	static constexpr std::string_view kName = "MoveProcess";
	static constexpr uint32_t kHashName = StringHash32(kName.data());

	static constexpr std::string_view GetName() { return kName; }
	static constexpr uint32_t GetHashName() { return kHashName; }
};

using MoveProcess = yang::BaseProcess<MoveProcessDescription, yang::TransformComponent, yang::MoveComponent>;