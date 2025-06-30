#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class PlayerActor;

class PlayerFactory
{
public:
	std::unique_ptr<PlayerActor> CreatePlayer();

private:
};

