#include "GAP321Game.h"
#include <Utils/Logger.h>
#include <Logic/Actor/Actor.h>
#include <Logic/Actor/ActorFactory.h>
#include <Logic/Event/Events/CreateActorEvent.h>
#include <Logic/Event/EventDispatcher.h>
#include <Logic/Process/MoveProcess.h>
#include <Logic/Process/RotationProcess.h>
#include <Logic/Process/KinematicMovement.h>
#include <Logic/Scenes/MainScene.h>
#include <Logic/Collision/CameraCollisionCallback.h>
#include <Logic/Components/AgentComponent.h>
#include <Logic/Components/VisionComponent.h>
#include <Logic/Components/MapComponent.h>
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
    RegisterBehaviors();

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
    m_actorFactory.RegisterComponent<AgentComponent>();
    m_actorFactory.RegisterComponent<VisionComponent>();
    m_actorFactory.RegisterComponent<MapComponent>();
}

void GAP321Game::RegisterProcesses()
{
    m_processFactory.RegisterProcess<RotationProcess>();
    m_processFactory.RegisterProcess<MoveProcess>();
    m_processFactory.RegisterProcess<KinematicMovement>();
}

void GAP321Game::RegisterViews()
{
    m_viewFactory.RegisterView<CameraView>();
}

void GAP321Game::RegisterScenes()
{
    RegisterScene<MainScene>();
}

void GAP321Game::RegisterBehaviors()
{

}
