#pragma once
#include <Logic/Scene/Scene.h>
#include <Utils/StringHash.h>

class MainScene : public yang::Scene
{
public:
    MainScene(yang::IGameLayer& owner);
    ~MainScene();

    virtual bool InitImpl(tinyxml2::XMLElement* pData) override final;
    virtual void OnSceneLoad() override final;     // Subscribe for events
    virtual void OnScenePause() override final;    // Do stuff when scene pauses (unsubscribe from events?)
    virtual void OnSceneResume() override final;   // Do stuff when scene becomes active (subscribe for events again?)
    virtual void OnSceneUnload() override final;   // Do stuff when scene unloads?

    static constexpr std::string_view kName = "MainScene";
    static constexpr uint32_t kHashName = StringHash32(kName.data());
    static constexpr std::string_view GetName() { return kName; }
    static constexpr uint32_t GetHashName() { return kHashName; }
private:

};