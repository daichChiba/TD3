#include "EnemyManager.h"
#include "../ActorManager.h"

#include "EnemyTest.h"

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

	Manager_.push_back(std::make_shared<EnemyTest>());

	for (const auto& enemy : Manager_) {
		enemy->Initialize(model_, bulletModel_, Vector3{pos}, actorManager_);
	}

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


