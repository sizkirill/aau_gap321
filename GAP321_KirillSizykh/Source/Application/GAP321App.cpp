#include "GAP321APP.h"

#include <Logic/GAP321Game.h>

std::unique_ptr<yang::IGameLayer> GAP321App::CreateGameLayer()
{
	return std::make_unique<GAP321Game>();
}
