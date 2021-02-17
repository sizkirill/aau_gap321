#pragma once

#include <Logic/Collisions/ICollisionCalback.h>
#include <string_view>
#include <Utils/StringHash.h>

class CameraCollisionCallback : public yang::ICollisionCallback
{
public:
    CameraCollisionCallback();
    virtual bool Init(tinyxml2::XMLElement* pData) override final;
    virtual void OnCollisionStart(yang::ColliderComponent* pFirst, yang::ColliderComponent* pSecond) override final;
    virtual void OnCollisionEnd(yang::ColliderComponent* pFirst, yang::ColliderComponent* pSecond) override final;
    virtual void UpdateCollision(yang::ColliderComponent* pFirst, yang::ColliderComponent* pSecond, float deltaSeconds) override final;

    static constexpr std::string_view GetName() { return kName; }
    static constexpr uint32_t GetHashName() { return kHashName; }
private:
    static constexpr std::string_view kName = "CameraCollisionCallback";
    static constexpr uint32_t kHashName = StringHash32(kName.data());

};