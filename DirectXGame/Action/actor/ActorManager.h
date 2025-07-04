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

	ActorManager();
	~ActorManager();

	Camera* SetCamera() { return camera_; }

	void SetGeamScene(GameScene* gameScene) { gameScene_ = gameScene;};

	PlayerActor* GetPlayer();

	void AddBullet(std::shared_ptr<BulletActor> attack) { attack_.push_back(attack); }

	void CheckStartPuzule();

	int GetEnemyDeadConnt() { return enemyDeadConnt; }

	int GetClearEnemyCount() { return clearEnemyCount; }

private:
	void CheckAllCollisions();
	

	Model* PlayeModel_,* PlayerBulletModel_,* longModel_, *shortModel_,*flyModel_,* enemyBulletModel_;

	Camera* camera_;
	FollowCamera* followCamera_;
	GameScene* gameScene_;

	std::unique_ptr <PlayerManager> playerManager_;
	std::unique_ptr < EnemyManager> enemyManager_;
	std::list<std::shared_ptr<BulletActor>> attack_;

	Vector3 preCameraRot;

	int enemyDeadConnt = 0;

	static inline const int startPazleCount = 3;
	static inline const int clearEnemyCount = 8;

};

