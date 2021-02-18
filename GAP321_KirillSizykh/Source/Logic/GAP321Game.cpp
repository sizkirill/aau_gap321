#include "GAP321Game.h"
#include <Utils/Logger.h>
#include <Logic/Actor/Actor.h>
#include <Logic/Actor/ActorFactory.h>
#include <Logic/Event/Events/CreateActorEvent.h>
#include <Logic/Event/EventDispatcher.h>
#include <Logic/Process/MoveProcess.h>
#include <Logic/Process/RotationProcess.h>
#include <Logic/Scenes/MainScene.h>
#include <Logic/Collision/CameraCollisionCallback.h>
#include <Application/Resources/ResourceCache.h>
#include <Views/CameraView.h>

#include <memory>
#include <cassert>

bool GAP321Game::Init(const yang::ApplicationLayer& app)
{
    LOG_CATEGORY("GAP321_KirillSizykh", 0, Green, Dark);

    if (!yang::IGameLayer::Init(app))
    {
        LOG(Error, "Failed to initialize GameLayer");
        return false;
    }

    RegisterEvents();
    RegisterComponents();
    RegisterCollisionCallbacks();
    RegisterProcesses();
    RegisterViews();
    RegisterScenes();

    LoadSceneAndSwitch("Assets/Scenes/MainScene.xml");

    return true;
}

void GAP321Game::RegisterEvents()
{
}

void GAP321Game::RegisterCollisionCallbacks()
{
    m_collisionCallbackFactory.RegisterCollisionCallback<CameraCollisionCallback>();
}

void GAP321Game::RegisterComponents()
{
}

void GAP321Game::RegisterProcesses()
{
    m_processFactory.RegisterProcess<RotationProcess>();
    m_processFactory.RegisterProcess<MoveProcess>();
}

void GAP321Game::RegisterViews()
{
    m_viewFactory.RegisterView<CameraView>();
}

void GAP321Game::RegisterScenes()
{
    RegisterScene<MainScene>();
}
