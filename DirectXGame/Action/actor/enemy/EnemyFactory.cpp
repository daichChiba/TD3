#include "EnemyFactory.h"

#include "EnemyActor.h"
#include "EnemyTest.h"

std::shared_ptr<EnemyActor> EnemyFactory::CreateEnemy() {
	std::shared_ptr<EnemyActor> player = std::make_unique<EnemyTest>();

	return player;
}
