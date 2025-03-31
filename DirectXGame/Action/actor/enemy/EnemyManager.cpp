#include "EnemyManager.h"
#include "../ActorManager.h"

#include "EnemyFactory.h"
#include "EnemyShort.h"
#include "EnemyFly.h"

void EnemyManager::Initialize(Model* longModel, Model* shortModel, Model* flyModel, Model* bulletModel, const Vector3 pos, ActorManager* actorManager) {
#ifdef _DEBUG
	assert(longModel);
	assert(shortModel);
	assert(flyModel);
	assert(bulletModel);
#endif // _DEBUG

	longModel_ = longModel;
	shortModel_ = shortModel;
	flyModel_ = flyModel;
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

void EnemyManager::CreateEnemyLong() {
	// 新しいEnemyLongを作成
	std::shared_ptr<EnemyActor> newEnemy = factory_->CreateLong();
	// 初期化
	newEnemy->Initialize(longModel_, bulletModel_, Startpos_, actorManager_);
	// 管理リストに追加
	Manager_.push_back(newEnemy);
}

void EnemyManager::CreateEnemyShort() {
	// 新しいEnemyShortを作成
	std::shared_ptr<EnemyActor> newEnemy = factory_->CreateShort();
	// 初期化
	newEnemy->Initialize(shortModel_, bulletModel_, Startpos_, actorManager_);
	// 管理リストに追加
	Manager_.push_back(newEnemy);
}

void EnemyManager::CreateEnemyFly() {
	// 新しいEnemyFlyを作成
	std::shared_ptr<EnemyActor> newEnemy = factory_->CreateFly();
	// 初期化
	newEnemy->Initialize(flyModel_, bulletModel_, Startpos_, actorManager_);
	// 管理リストに追加
	Manager_.push_back(newEnemy);
}

