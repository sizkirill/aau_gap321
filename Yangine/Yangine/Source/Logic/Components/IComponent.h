#pragma once
#include <stdint.h>
#include <string>
#include <memory>
#include <Utils/Typedefs.h>

#ifdef DEBUG_PANEL
#include <Logic/Scene/DebugPanel.h>
#endif

/** \file IComponent.h */
/** IComponent interface description */

namespace tinyxml2
{
    class XMLElement;
}
//! \namespace yang Contains all Yangine code
namespace yang
{
    class Actor;
    class IGraphics;
    class ActorFactory;

/** \class IComponent */
/** Base class for all actor components */
class IComponent
{
public:
	/// Constructor
    /// \param pOwner - Actor that owns the component
    /// \param name - Name of the component
    IComponent(Actor* pOwner, const char* name);

	/** Default Destructor */
	virtual ~IComponent();

    /// Initialize the component from an XML element
    /// \param pData - XML Element that contains component data
    /// \return true if initialized successfully
    virtual bool Init(tinyxml2::XMLElement* pData) = 0;

    /// Get references to other needed components after all actors components were initialized
    /// \return true if successful
    virtual bool PostInit() { return true; }

    /// Update component data
    /// \param deltaSeconds - number of seconds passed since the last frame
    virtual void Update(float deltaSeconds) {}

    /// Draw the component
    /// \param pGraphics - graphics system to use
    /// \return true if render was successful
    virtual bool Render(IGraphics* pGraphics) { return true; }

#ifdef DEBUG_PANEL
    virtual void AttachToDebugPanel(DebugPanel& panel, DebugPanel::ActorSection& actorSection) const {}
#endif

    /// Hash the name of the component into a 32-bit integer
    /// \param name - component name
    /// \return hashed value
    static Id HashName(const char* name);

    template <uint32_t ComponentHashName, class... Args>
    static std::unique_ptr<IComponent> CreateComponent(Actor* pOwner, Args... args);

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
    Actor* m_pOwner;    ///< Actor, owning this component
    Id m_id;            ///< Hash value of this component's name

public:
    /// Get this component id
    Id GetId() { return m_id; }

    /// Get actor that owns this component
    Actor* GetOwner() const { return m_pOwner; }
};
}