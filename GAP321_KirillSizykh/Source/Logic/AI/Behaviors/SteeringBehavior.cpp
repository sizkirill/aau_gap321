#include "SteeringBehavior.h"
#include <Logic/Actor/Actor.h>
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/Kinematic/KinematicComponent.h>
#include <Utils/Logger.h>
#include <cassert>

bool SteeringBehavior::Init(yang::Actor* pAgent)
{
    assert(pAgent);

    m_pAgentKinematicData = pAgent->GetComponent<yang::KinematicComponent>();

    if (!m_pAgentKinematicData)
    {
        LOG(Error, "Agent must have KinematicComponent");
        return false;
    }

    m_pAgentTransform = pAgent->GetComponent<yang::TransformComponent>();

    if (!m_pAgentTransform)
    {
        LOG(Error, "Agent must have TransformComponent");
        return false;
    }

    return true;
}
