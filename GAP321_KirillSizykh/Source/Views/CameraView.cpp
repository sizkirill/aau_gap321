#include "CameraView.h"
#include <Application/ApplicationLayer.h>
#include <Application/Graphics/IGraphics.h>
#include <Logic/Actor/Actor.h>

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::unique_ptr<yang::IView> yang::IView::CreateView<CameraView::GetHashName()>()
{
    return std::make_unique<CameraView>();
};

#pragma warning(pop)

CameraView::CameraView()
    :m_pGraphics(nullptr)
    ,m_pKeyboard(nullptr)
    ,m_pMouse(nullptr)
    ,m_pAudio(nullptr)
    ,m_pGameLayer(nullptr)
{
}

bool CameraView::Init(const yang::ApplicationLayer& app, tinyxml2::XMLElement* pData)
{
    m_pGraphics = app.GetGraphics();
    m_pKeyboard = app.GetKeyboard();
    m_pMouse = app.GetMouse();
    m_pAudio = app.GetAudio();
    m_pGameLayer = app.GetGameLayer();

    return true;
}

void CameraView::UpdateInput()
{
}

void CameraView::ViewScene()
{
    auto& actors = m_pGameLayer->GetActors();
    for (auto& actorPair : actors)
    {
        actorPair.second->Render(m_pGraphics);
    }
}
