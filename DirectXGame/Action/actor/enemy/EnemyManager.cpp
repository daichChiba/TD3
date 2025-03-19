#include "EnemyManager.h"
#include "../ActorManager.h"

#include "EnemyFactory.h"
#include "EnemyShort.h"
#include "EnemyFly.h"

void EnemyManager::Initialize(Model* model, Model* bulletModel, const Vector3 pos, ActorManager* actorManager)
{
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;
	bulletModel_ = bulletModel;

	Startpos_ = pos;

	actorManager_ = actorManager;
	factory_ = new EnemyFactory();
	
	//factory_ = new PlayerFactory();
}

void EnemyManager::Update()
{
	for (const auto& enemy : Manager_) {
		enemy->Update();
	}
}

void EnemyManager::Draw(Camera& camera)
{
	for (const auto& enemy : Manager_) {
		enemy->Draw(camera);
	}
}

void EnemyManager::CreateEnemyTest()
{
	std::shared_ptr<EnemyActor> newEnemy = factory_->CreateEnemy();
	newEnemy->Initialize(model_, bulletModel_, Startpos_, actorManager_);
	Manager_.push_back(newEnemy);

}

void EnemyManager::CreateEnemyShort() { 
	std::shared_ptr<EnemyActor> newEnemy = factory_->CreateShort();
	newEnemy->Initialize(model_, bulletModel_, Startpos_, actorManager_);
	Manager_.push_back(newEnemy);
}

void EnemyManager::CreateEnemyFly() {
	std::shared_ptr<EnemyActor> newEnemy = factory_->CreateFly();
	newEnemy->Initialize(model_, bulletModel_, Startpos_, actorManager_);
	Manager_.push_back(newEnemy);
}


