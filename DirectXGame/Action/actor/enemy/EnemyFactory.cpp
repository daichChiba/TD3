#include "EnemyFactory.h"

#include "EnemyActor.h"
#include "EnemyTest.h"
#include "EnemyShort.h"

std::shared_ptr<EnemyActor> EnemyFactory::CreateEnemy() {
	std::shared_ptr<EnemyActor> player = std::make_unique<EnemyTest>();

	return player;
}

std::shared_ptr<EnemyActor> EnemyFactory::CreateShort() {
	std::shared_ptr<EnemyActor> player = std::make_unique<EnemyShort>();
	return player;
}
