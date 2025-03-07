#pragma once

#include "kamataEngine.h"

using namespace KamataEngine;

class EnemyActor;

class EnemyFactory {
public:
	std::shared_ptr<EnemyActor> CreateEnemy();

private:
};
