#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class PlayerManager;

class ActorManager
{
public:
	void Initialize(Model*  PlayeModel,Model*  PlayerBulletModel,Model*  enemyModel,Model*  enemyBulletModel);
	void Update();
	void Draw(Camera& camera);

	PlayerActor* GetPlayer();
private:
	Model* PlayeModel_,* PlayerBulletModel_,* enemyModel_,* enemyBulletModel_;

	PlayerManager* playerManager_;
};

