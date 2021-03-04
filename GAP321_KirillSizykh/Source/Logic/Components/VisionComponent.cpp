#include "VisionComponent.h"
#include <Utils/tinyxml2/tinyxml2.h>

using yang::IComponent;

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::unique_ptr<yang::IComponent> yang::IComponent::CreateComponent<VisionComponent::GetHashName()>(yang::Actor* pOwner) { return std::make_unique<VisionComponent>(pOwner); };

#pragma warning(pop)

VisionComponent::VisionComponent(yang::Actor* pOwner)
    :yang::ColliderComponent(pOwner, Type::kSensor, GetName())
{
	
}

bool VisionComponent::Init(tinyxml2::XMLElement* pData)
{
    using namespace tinyxml2;

    return yang::ColliderComponent::Init(pData);
}