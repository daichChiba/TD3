#include "ActorManager.h"

#include "../FolloCamera.h"

#include "player/PlayerManager.h"
#include "../../Scene/GameScene.h"

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

    playerManager_->GetPlayer()->camera_ = camera_;

    followCamera_->SetTarget(GetPlayer()->GetWorldTransfrom());
}


void ActorManager::Update()
{
    playerManager_->GetPlayer()->camera_->rotation_ = followCamera_->GetCamera().rotation_;
	playerManager_->Update();

    followCamera_->Update();
	camera_->matView = followCamera_->GetCamera().matView;
	camera_->matProjection = followCamera_->GetCamera().matProjection;
    
    camera_->TransferMatrix();
}

void ActorManager::Draw()
{
	playerManager_->Draw(*camera_);
}

PlayerActor* ActorManager::GetPlayer()
{
	return	playerManager_->GetPlayer();
}



