#pragma once

#include <string_view>
#include <Views/IView.h>
#include <Utils/StringHash.h>

namespace yang
{
    class IGraphics;
    class IKeyboard;
    class IMouse;
    class IAudio;
    class IGameLayer;
}

class CameraView : public yang::IView
{
public:
    CameraView();

    virtual bool Init(const yang::ApplicationLayer& app, tinyxml2::XMLElement* pData) override final;
    virtual void UpdateInput() override final;
    virtual void ViewScene() override final;

    static constexpr std::string_view kName = "CameraView";
    static constexpr uint32_t kHashName = StringHash32(kName.data());
    static constexpr std::string_view GetName() { return kName; }
    static constexpr uint32_t GetHashName() { return kHashName; }
private:
    yang::IGraphics* m_pGraphics;
    yang::IKeyboard* m_pKeyboard;
    yang::IMouse* m_pMouse;
    yang::IAudio* m_pAudio;
    yang::IGameLayer* m_pGameLayer;
};