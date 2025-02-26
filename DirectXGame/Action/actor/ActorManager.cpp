#include "ActorManager.h"

#include "player/PlayerManager.h"

void ActorManager::Initialize(Model*  PlayeModel,Model*  PlayerBulletModel,Model*  enemyModel,Model*  enemyBulletModel)
{
#ifdef _DEBUG
	assert(PlayeModel);
	assert(PlayerBulletModel);
	assert(enemyModel);
	assert(enemyBulletModel);
#endif

	PlayeModel_ = PlayeModel;
	PlayerBulletModel_ = PlayerBulletModel;
	enemyModel_ = enemyModel;
	enemyBulletModel_  = enemyBulletModel;

	playerManager_ = new PlayerManager();
	playerManager_->Initialize(PlayeModel_, PlayerBulletModel, Vector3{0.0f, 0.0f, 0.0f});

	playerManager_->CreatePlayerMain();
}

void ActorManager::Update()
{
	playerManager_->Update();
}

void ActorManager::Draw(Camera& camera)
{
	playerManager_->Draw(camera);
}

PlayerActor* ActorManager::GetPlayer()
{
	return	playerManager_->GetPlayer();
}


