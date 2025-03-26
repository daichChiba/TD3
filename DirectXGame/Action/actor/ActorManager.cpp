#include "ActorManager.h"

#include "../FolloCamera.h"

#include "../../Scene/GameScene.h"
#include "player/PlayerManager.h"

using namespace MathUtility;

void ActorManager::Initialize(Model* PlayeModel, Model* PlayerBulletModel, Model* enemyModel, Model* enemyBulletModel) {
#ifdef _DEBUG
	assert(PlayeModel);
	assert(PlayerBulletModel);
	assert(enemyModel);
	assert(enemyBulletModel);
#endif

	camera_ = new Camera();
	camera_->Initialize();

	followCamera_ = new FollowCamera();
	followCamera_->Initialize();

	PlayeModel_ = PlayeModel;
	PlayerBulletModel_ = PlayerBulletModel;
	enemyModel_ = enemyModel;
	enemyBulletModel_ = enemyBulletModel;

	playerManager_ = new PlayerManager();
	playerManager_->Initialize(PlayeModel_, PlayerBulletModel, Vector3{0.0f, 0.0f, 0.0f}, this);

	playerManager_->CreatePlayerMain();

	followCamera_->SetTarget(GetPlayer()->GetWorldTransfrom());


    enemyManager_ = new EnemyManager();
    enemyManager_->Initialize(enemyModel_, enemyBulletModel_, Vector3(5.0f, 0.0f, 0.0f), this);
	

   enemyManager_->CreateEnemyFly();
	
   /*enemyManager_->CreateEnemyShort();

	enemyManager_->CreateEnemyFly();*/
}

void ActorManager::Update() {
	enemyManager_->RandomCreate();
	
	playerManager_->GetPlayer()->SetCameraRot(followCamera_->GetCamera().rotation_);
	playerManager_->Update();

	for (std::shared_ptr<BulletActor> bullet : attack_)
	{
		bullet->Update();
	}
	attack_.remove_if([](std::shared_ptr<BulletActor> a) { return a->IsDelete(); });

    enemyManager_->Update();

	followCamera_->Update();
	followCamera_->DrawImgui();
	
	camera_->matView = followCamera_->GetCamera().matView;
	camera_->matProjection = followCamera_->GetCamera().matProjection;

	camera_->TransferMatrix();

	CheckAllCollisions();

	
	
}

void ActorManager::Draw() { 
	playerManager_->Draw(*camera_); 
	for (std::shared_ptr<BulletActor> bullet : attack_)
	{
		bullet->Draw(*camera_);
	}

	enemyManager_->Draw(*camera_);
}

PlayerActor* ActorManager::GetPlayer() { return playerManager_->GetPlayer(); }

void ActorManager::CheckAllCollisions()
{
	
#pragma region
	 for (auto& bullet : attack_) {
        for (auto& enemy : enemyManager_->GetEnemy()) {
            // 距離を計算して当たり判定を行う
            Vector3 diff = enemy->GetWorldPosition() - bullet->GetWorldPosition();
            float distance = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

            if (distance < (bullet->GetRadius() + enemy->GetRadius())) {
                // 当たった場合の処理
                bullet->OnCollision();
                enemy->OnCollision();
            }
        }
    }
#pragma endregion
}
