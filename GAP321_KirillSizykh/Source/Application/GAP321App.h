#pragma once
#include <Application/ApplicationLayer.h>

class GAP321App : public yang::ApplicationLayer
{
public:
	GAP321App() = default;

	~GAP321App() = default;

	std::unique_ptr<yang::IGameLayer> CreateGameLayer() override final;

private:

public:

};
