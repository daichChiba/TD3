#include "EnemyFactory.h"

#include "EnemyActor.h"
#include "EnemyTest.h"

std::unique_ptr<EnemyActor> EnemyFactory::CreateEnemy() {
	std::unique_ptr<EnemyActor> player = std::make_unique<EnemyTest>();

	return player;
}
