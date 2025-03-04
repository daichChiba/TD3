#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class FollowCamera;
class PlayerManager;
class PlayerActor;
class GameScene;

class ActorManager
{
public:
	void Initialize(Model*  PlayeModel,Model*  PlayerBulletModel,Model*  enemyModel,Model*  enemyBulletModel);
	void Update();
	void Draw();

	Camera* SetCamera(){ return camera_; }

	void SetGeamScene(GameScene* gameScene) { gameScene_ = gameScene;};
	PlayerActor* GetPlayer();

private:
	Model* PlayeModel_,* PlayerBulletModel_,* enemyModel_,* enemyBulletModel_;

	Camera* camera_;
	FollowCamera* followCamera_;
	GameScene* gameScene_;

	PlayerManager* playerManager_;

	Vector3 preCameraRot;
};

