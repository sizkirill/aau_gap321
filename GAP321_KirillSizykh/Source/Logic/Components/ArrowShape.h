/** \file ArrowShape.h */
/** ArrowShape class description */
#pragma once
#include <Logic/Components/IComponent.h>
#include <Utils/Vector2.h>
#include <Utils/Color.h>
#include <Utils/StringHash.h>

namespace yang
{
    class TransformComponent;
}

/** \class ArrowShape */
/** Component that describes an arrow shape */
class ArrowShape : public yang::IComponent 
{
public:

    /// Constructor
    /// \param pOwner - actor, that owns this component
    ArrowShape(yang::Actor* pOwner);

    /** Default Destructor */
    ~ArrowShape() = default;

    /// Initialize the component from an XML element
    /// \param pData - XML Element that contains component data
    /// \return true if initialized successfully
    virtual bool Init(tinyxml2::XMLElement* pData) override;

    /// Obtains reference to actor's transform component
    /// \return true if actor has transform component
    virtual bool PostInit() override;

    /// Draw the arrow shape
    /// \param pGraphics - graphics system to use
    /// \return true if render was successful
    virtual bool Render(yang::IGraphics* pGraphics) override;

    static constexpr std::string_view kName = "ArrowShape";
    static constexpr uint32_t kHashName = StringHash32(kName.data());
    static constexpr const char* GetName() { return kName.data(); }
    static constexpr uint32_t GetHashName() { return kHashName; }

private:
    yang::FVec2 m_vertices[4];                      ///< Arrow shape vertices
    yang::FVec2 m_transformedVertices[4];
    yang::IColor m_color;                           ///< Color to draw
    yang::TransformComponent* m_pActorTransform;    ///< Owner's transform component
};