#pragma once
/** \file MapComponent.h */
/** TODO: File Purpose */

#include <Logic/Components/IComponent.h>
#include <Logic/AI/Pathfinding/GraphSearcher.h>

class BasicPathfindingMap;

/** \class MapComponent */
/** TODO: Class Purpose */
class MapComponent : public yang::IComponent
{
public:
	/// Default constructor
    /// \param pOwner - Actor owning this component
	MapComponent(yang::Actor* pOwner);

	/// The name of this component
	/// \return "MapComponent"
	static constexpr const char* GetName() {return "MapComponent"; }

	/// Initializes MapComponent from XMLElement
	/// \param pData - pointer to XMLElement to initialize MapComponent from.
	/// \return true if initialized successfully
	virtual bool Init(tinyxml2::XMLElement* pData) override final;
	
	virtual bool Render(yang::IGraphics* pGraphics) override final;

	virtual void Update(float deltaSeconds) override final;

private:
	std::shared_ptr<BasicPathfindingMap> m_pMap;
	std::unique_ptr<GraphSearcher> m_pGraphSearcher;
};