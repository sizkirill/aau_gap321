#include "CameraCollisionCallback.h"
#include <Application/ApplicationConstants.h>
#include <Logic/Components/Colliders/ColliderComponent.h>
#include <Logic/Components/TransformComponent.h>
#include <Logic/Actor/Actor.h>

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::unique_ptr<yang::ICollisionCallback> yang::ICollisionCallback::CreateCollisionCallback<CameraCollisionCallback::GetHashName()>()
{
    return std::make_unique<CameraCollisionCallback>();
};

#pragma warning(pop)

CameraCollisionCallback::CameraCollisionCallback()
{
}

bool CameraCollisionCallback::Init(tinyxml2::XMLElement* pData)
{
    return true;
}

void CameraCollisionCallback::OnCollisionStart(yang::ColliderComponent* pFirst, yang::ColliderComponent* pSecond)
{
}

void CameraCollisionCallback::OnCollisionEnd(yang::ColliderComponent* pFirst, yang::ColliderComponent* pSecond)
{
    auto pTransform = pSecond->GetOwner()->GetComponent<yang::TransformComponent>();

    if (!pTransform)
    {
        return;
    }

    auto& transformPosition = pTransform->GetPosition();
    yang::FVec2 delta = transformPosition - yang::FVec2(yang::kWindowWidth / 2.f, yang::kWindowHeight / 2.f);

    if (transformPosition.x > yang::kWindowWidth || transformPosition.x < 0)
    {
        transformPosition.x = transformPosition.x - 2.f * delta.x;
    }
    if (transformPosition.y > yang::kWindowHeight || transformPosition.y < 0)
    {
        transformPosition.y = transformPosition.y - 2.f * delta.y;
    }
}

void CameraCollisionCallback::UpdateCollision(yang::ColliderComponent* pFirst, yang::ColliderComponent* pSecond, float deltaSeconds)
{
}
