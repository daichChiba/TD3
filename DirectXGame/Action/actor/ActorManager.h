#pragma once
#include "KamataEngine.h"

#include "bullet/BulletActor.h"

using namespace KamataEngine;

class FollowCamera;
class PlayerManager;
class PlayerActor;
class EnemyManager;
class EnemyActor;
class GameScene;

class ActorManager
{
public:
	void Initialize(Model* PlayeModel, Model* PlayerBulletModel, Model* longModel, Model* shortModel, Model* flyModel, Model* enemyBulletModel);
	void Update();
	void Draw();

	Camera* SetCamera(){ return camera_; }

	void SetGeamScene(GameScene* gameScene) { gameScene_ = gameScene;};

	PlayerActor* GetPlayer();

	void AddBullet(std::shared_ptr<BulletActor> attack) { attack_.push_back(attack); }

private:
	void CheckAllCollisions();
	void CheckStartPuzule();

	Model* PlayeModel_ = nullptr;
    Model* PlayerBulletModel_ = nullptr;
    Model* longModel_ = nullptr;
    Model* shortModel_ = nullptr;
    Model* flyModel_ = nullptr;
    Model* enemyBulletModel_ = nullptr;

	Camera* camera_;
	FollowCamera* followCamera_;
	GameScene* gameScene_;

	PlayerManager* playerManager_;
	EnemyManager* enemyManager_;
	std::list<std::shared_ptr<BulletActor>> attack_;

	Vector3 preCameraRot;

	int enemyDeadConnt = 0;

	static inline const int startPazleCount = 1;
	static inline const int clearEnemyCount = 2;
};

