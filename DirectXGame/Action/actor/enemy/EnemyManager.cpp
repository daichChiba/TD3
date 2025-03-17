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

void EnemyManager::CreateEnemyTest() {
	// 新しい敵を生成する
	std::shared_ptr<EnemyActor> newEnemy = factory_->CreateEnemy();
	test++;
	Startpos_.x = test;                                                   // 敵の開始位置を更新
	newEnemy->Initialize(model_, bulletModel_, Startpos_, actorManager_); // 敵を初期化
	Manager_.push_back(newEnemy);                                         // 敵を管理リストに追加
}

void EnemyManager::CreateEnemyShort() {
	// 新しい近距離攻撃の敵を生成する
	std::shared_ptr<EnemyActor> newEnemy = factory_->CreateShort();
	test++;
	Startpos_.x = test;                                                   // 敵の開始位置を更新
	newEnemy->Initialize(model_, bulletModel_, Startpos_, actorManager_); // 敵を初期化
	Manager_.push_back(newEnemy);                                         // 敵を管理リストに追加
}

void EnemyManager::CreateEnemyFly() {
	// 新しい飛行する敵を生成する
	std::shared_ptr<EnemyActor> newEnemy = factory_->CreateFly();
	test++;
	Startpos_.z = test;                                                   // 敵の開始位置を更新
	newEnemy->Initialize(model_, bulletModel_, Startpos_, actorManager_); // 敵を初期化
	Manager_.push_back(newEnemy);                                         // 敵を管理リストに追加
}

