#include "EnemyManager.h"
#include "../ActorManager.h"
#include "../player/PlayerActor.h"

#include "EnemyFactory.h"
#include "EnemyFly.h"
#include "EnemyShort.h"

using namespace MathUtility;

void EnemyManager::Initialize(Model* model, Model* bulletModel, const Vector3 pos, ActorManager* actorManager) {
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;
	bulletModel_ = bulletModel;

	Startpos_ = pos;

	actorManager_ = actorManager;
	factory_ = new EnemyFactory();

	// factory_ = new PlayerFactory();
}

void EnemyManager::Update() {
	for (const auto& enemy : Manager_) {
		enemy->Update();
	}
	Manager_.remove_if([](std::shared_ptr<EnemyActor> a) { return a->IsDelete(); });
}

void EnemyManager::Draw(Camera& camera) {
	for (const auto& enemy : Manager_) {
		enemy->Draw(camera);
	}
}

void EnemyManager::RandomCreate() {
	createTimer_ -= 1.0f / 60.0f;
	if (createTimer_ < 0.0f) {
		int enemyc = rand() % 100 + 1;
		createTimer_ = createCoolTime_;
		// 円周上のランダムな位置を計算
		float radius = 10.0f;// 円の半径
		float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * PI; // ランダムな角度
		Startpos_ = {
			actorManager_->GetPlayer()->GetWorldTransfrom()->translation_.x + radius * std::cos(angle), 
			0.0f,
			actorManager_->GetPlayer()->GetWorldTransfrom()->translation_.z + radius * std::sin(angle)};

		if (enemyc < fluEnemy) {
			CreateEnemyFly();
			return;
		} else if (enemyc < longEnemy) {
			CreateEnemyTest();
			return;
		} else if (enemyc < shortEnemy) {
			CreateEnemyShort();
			return;
		}
	}
}

void EnemyManager::CreateEnemyTest() {
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
