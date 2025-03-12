#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class EnemyActor;

class EnemyFactory {
public:
	std::shared_ptr<EnemyActor> CreateEnemy();
	std::shared_ptr<EnemyActor> CreateShort();
	std::shared_ptr<EnemyActor> CreateFly();

private:
};
