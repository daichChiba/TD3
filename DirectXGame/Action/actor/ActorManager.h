#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class FollowCamera;
class PlayerManager;
class PlayerActor;

class ActorManager
{
public:
	void Initialize(Model*  PlayeModel,Model*  PlayerBulletModel,Model*  enemyModel,Model*  enemyBulletModel);
	void Update();
	void Draw();

	PlayerActor* GetPlayer();
	Camera& GetCamera() { return camera_; }
private:
	Model* PlayeModel_,* PlayerBulletModel_,* enemyModel_,* enemyBulletModel_;

	Camera camera_;
	FollowCamera* followCamera_;

	PlayerManager* playerManager_;
};

