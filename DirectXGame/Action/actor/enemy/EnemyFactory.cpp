#include "EnemyFactory.h"

#include "EnemyActor.h"
#include "EnemyTest.h"
#include "EnemyShort.h"
#include "EnemyFly.h"

std::shared_ptr<EnemyActor> EnemyFactory::CreateEnemy() {
	std::shared_ptr<EnemyActor> player = std::make_unique<EnemyTest>();

	return player;
}

std::shared_ptr<EnemyActor> EnemyFactory::CreateShort() {
	std::shared_ptr<EnemyActor> player = std::make_unique<EnemyShort>();
	return player;
}

std::shared_ptr<EnemyActor> EnemyFactory::CreateFly() { 
	std::shared_ptr<EnemyActor> player = std::make_unique<EnemyFly>();
	return player;
}
