#include "ActorManager.h"

#include "../FolloCamera.h"

#include "../../Scene/GameScene.h"
#include "enemy/EnemyManager.h"
#include "enemy/enemyActor.h"
#include "player/PlayerManager.h"

using namespace MathUtility;

void ActorManager::Initialize(Model* PlayeModel, Model* PlayerBulletModel, Model* longModel, Model* shortModel, Model* flyModel, Model* enemyBulletModel) {
#ifdef _DEBUG
	assert(PlayeModel);
	assert(PlayerBulletModel);
	assert(longModel);
	assert(shortModel);
	assert(flyModel);
	assert(enemyBulletModel);
#endif

	camera_ = new Camera();
	camera_->Initialize();

	followCamera_ = new FollowCamera();
	followCamera_->Initialize();

	PlayeModel_ = PlayeModel;
	PlayerBulletModel_ = PlayerBulletModel;
	longModel_ = longModel;
	shortModel_ = shortModel;
	flyModel_ = flyModel;
	enemyBulletModel_ = enemyBulletModel;

	playerManager_ = std::make_unique< PlayerManager>();
	playerManager_->Initialize(PlayeModel_, PlayerBulletModel, Vector3{0.0f, 0.0f, 0.0f}, this);

	playerManager_->CreatePlayerMain();

	followCamera_->SetTarget(GetPlayer()->GetWorldTransfrom());

	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->Initialize(longModel_, shortModel_, flyModel_, enemyBulletModel_, Vector3(5.0f, 0.0f, 0.0f), this);

	followCamera_->SetTarget(GetPlayer()->GetWorldTransfrom());

	enemyDeadConnt = 0;
}

void ActorManager::Update() {
	enemyManager_->RandomCreate();

	playerManager_->GetPlayer()->SetCameraRot(followCamera_->GetCamera().rotation_);
	playerManager_->Update();

	enemyManager_->Update();

	for (std::shared_ptr<BulletActor> bullet : attack_) {
		bullet->Update();
	}
	attack_.remove_if([](std::shared_ptr<BulletActor> a) { return a->IsDelete(); });

	followCamera_->Update();
	followCamera_->DrawImgui();

	camera_->matView = followCamera_->GetCamera().matView;
	camera_->matProjection = followCamera_->GetCamera().matProjection;

	camera_->TransferMatrix();

	CheckAllCollisions();

	CheckStartPuzule();

#ifdef _DEBUG

	ImGui::Begin("gamescene");
	ImGui::Text("enemyDeadConnt : %d", enemyDeadConnt);
	ImGui::End();
#endif // _DEBUG
}

void ActorManager::Draw() {
	playerManager_->Draw(*camera_);
	for (std::shared_ptr<BulletActor> bullet : attack_) {
		bullet->Draw(*camera_);
	}

	enemyManager_->Draw(*camera_);
}

ActorManager::ActorManager() {}

ActorManager::~ActorManager() {  }

PlayerActor* ActorManager::GetPlayer() { return playerManager_->GetPlayer(); }

void ActorManager::CheckAllCollisions() {

#pragma region
	for (auto& enemy : enemyManager_->GetEnemy()) {
		Vector3 diff = enemy->GetWorldPosition() - playerManager_->GetPlayer()->GetWorldTransfrom()->translation_;
		float distance = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
		if (distance < (enemy->GetRadius() + playerManager_->GetPlayer()->GetRadius()) && playerManager_->GetPlayer()->IsHitCoolDown()) {

			playerManager_->GetPlayer()->OnCollision();
		}
	}
	for (auto& bullet : attack_) {
		if (bullet->GetBulletType() == BulletType::enemy) {

			Vector3 diff = playerManager_->GetPlayer()->GetWorldTransfrom()->translation_ - bullet->GetWorldPosition();
			float distance = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

			if (distance < (bullet->GetRadius() + playerManager_->GetPlayer()->GetRadius()) && playerManager_->GetPlayer()->IsHitCoolDown()) {

				bullet->OnCollision();
				playerManager_->GetPlayer()->OnCollision();
			}
		} else if (bullet->GetBulletType() == BulletType::player) {

			for (auto& enemy : enemyManager_->GetEnemy()) {
				Vector3 diff = enemy->GetWorldPosition() - bullet->GetWorldPosition();
				float distance = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

				if (distance < (bullet->GetRadius() + enemy->GetRadius())) {

					bullet->OnCollision();
					enemy->OnCollision(bullet->GetDamage());
				}
			}
		}
	}

#pragma endregion
}

void ActorManager::CheckStartPuzule() {
	for (const auto& enemy : enemyManager_->GetEnemy()) {
		if (enemy->IsDelete()) {
			enemyDeadConnt++;
		}
	}

	if (enemyDeadConnt >= startPazleCount && (gameScene_->puzzleClear) == false) {
		gameScene_->isStop = true;
	}
	if (enemyDeadConnt >= clearEnemyCount && gameScene_->puzzleClear == true) {

		gameScene_->isClear = true;
		gameScene_->isEnd = true;
	}
}
