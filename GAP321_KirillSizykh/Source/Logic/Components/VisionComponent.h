#pragma once
/** \file VisionComponent.h */
/** TODO: File Purpose */

#include <Logic/Components/Colliders/ColliderComponent.h>
#include <Utils/StringHash.h>
#include <string_view>

/** \class VisionComponent */
/** TODO: Class Purpose */
class VisionComponent : public yang::ColliderComponent
{
public:
	/// Default constructor
        /// \param pOwner - Actor owning this component
	VisionComponent(yang::Actor* pOwner);

	/// Initializes VisionComponent from XMLElement
	/// \param pData - pointer to XMLElement to initialize VisionComponent from.
	/// \return true if initialized successfully
	virtual bool Init(tinyxml2::XMLElement* pData) override final;
	
	static constexpr std::string_view kName = "VisionComponent";
	static constexpr uint32_t kHashName = StringHash32(kName.data());

	static constexpr const char* GetName() { return kName.data(); }
	static constexpr uint32_t GetHashName() { return kHashName; }
private:


};