#include "ArrowShape.h"
#include <Application/Graphics/IGraphics.h>
#include <Logic/Components/TransformComponent.h>
#include <Logic/Actor/Actor.h>
#include <Utils/TinyXml2/tinyxml2.h>
#include <Utils/Logger.h>
#include <Utils/Matrix.h>
#include <cassert>

#pragma warning(push)
#pragma warning(disable:4307)

template<>
std::unique_ptr<yang::IComponent> yang::IComponent::CreateComponent<ArrowShape::GetHashName()>(yang::Actor* pOwner)
{
    return std::make_unique<ArrowShape>(pOwner);
};

#pragma warning(pop)

ArrowShape::ArrowShape(yang::Actor* pOwner)
    :IComponent(pOwner, kName.data())
{
}

bool ArrowShape::Init(tinyxml2::XMLElement* pData)
{
    using namespace tinyxml2;

    XMLElement* pVertex = pData->FirstChildElement("Vertex");
    size_t vertexCount = 0;

    while (pVertex && vertexCount < 4)
    {
        m_vertices[vertexCount].x = pVertex->FloatAttribute("x");
        m_vertices[vertexCount].y = pVertex->FloatAttribute("y");
        pVertex = pVertex->NextSiblingElement("Vertex");
        ++vertexCount;
    }
    
    if (vertexCount < 4)
    {
        LOG(Error, "ArrowShape requires 4 vertices");
        return false;
    }

    memcpy(m_transformedVertices, m_vertices, sizeof(m_vertices));

    if (pVertex)
    {
        LOG(Warning, "ArrowShape requires only 4 vertices, all others are ignored");
    }

    XMLElement* pColor = pData->FirstChildElement("Color");

    if (pColor)
    {
        m_color = yang::IColor(pColor->IntAttribute("r"), pColor->IntAttribute("g"), pColor->IntAttribute("b"), pColor->IntAttribute("a", 255));
    }

    return true;
}

bool ArrowShape::PostInit()
{
    m_pActorTransform = GetOwner()->GetComponent<yang::TransformComponent>();

    if (!m_pActorTransform)
    {
        LOG(Error, "Actor doesn't have transform component. Unable to initialize ArrowShape");
        return false;
    }

    return true;
}

bool ArrowShape::Render(yang::IGraphics* pGraphics)
{
    assert(m_pActorTransform);

    if (m_pActorTransform->MatrixNeedUpdate())
    {
        auto& transform = m_pActorTransform->GetCurrentTransform();

        std::transform(m_vertices, m_vertices + sizeof(m_vertices)/sizeof(*m_vertices), m_transformedVertices,
            [transform](yang::FVec2 v) {return transform.TransformPoint(v); });
    }
    
    pGraphics->SetDrawColor(m_color);
    pGraphics->FillTriangle(m_transformedVertices);
    pGraphics->FillTriangle(m_transformedVertices + 1);

    return true;
}
