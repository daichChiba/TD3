#include "PlayerFactory.h"

#include "PlayerActor.h"
#include "PlayerMain.h"

std::unique_ptr<PlayerActor> PlayerFactory::CreatePlayer()
{
	std::unique_ptr<PlayerActor>player = std::make_unique<PlayerMain>();

	return player;
}
