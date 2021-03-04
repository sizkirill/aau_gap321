#include "MainScene.h"
#include <Logic/Event/EventDispatcher.h>
#include <Logic/Event/Input/KeyboardInputEvent.h>
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/Colliders/ColliderComponent.h>
#include <Logic/Shapes/CircleShape.h>
#include <Logic/Actor/Actor.h>
#include <Utils/Random.h>
#include <Utils/TinyXml2/tinyxml2.h>

#include <cassert>

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::shared_ptr<yang::Scene> yang::Scene::CreateScene<MainScene::GetHashName()>(yang::IGameLayer& owner)
{
    return std::make_shared<MainScene>(owner);
};

#pragma warning(pop)

MainScene::MainScene(yang::IGameLayer& owner)
    :yang::Scene(owner)
{
}

MainScene::~MainScene()
{

}

bool MainScene::InitImpl(tinyxml2::XMLElement* pData)
{

    return true;
}

void MainScene::OnSceneLoad()
{

}

void MainScene::OnScenePause()
{

}

void MainScene::OnSceneResume()
{

}

void MainScene::OnSceneUnload()
{

}
