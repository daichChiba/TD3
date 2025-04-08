#pragma once
#include "../Action/actor/ActorManager.h"
#include <KamataEngine.h>

#include "../Action/actor/enemy/EnemyManager.h"

using namespace KamataEngine;

class FollowCamera;

class GameScene {
public:
	// メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool puzzleClear = false;

	bool isStop = false;
	bool isEnd = false;
	bool isClear = false;

		// デスフラグのgetter
	bool IsStop() const { return isStop; }
	void SetIsStop() { isStop = !isStop; }
	bool IsFinished() const { return isEnd; }
	bool IsClear() const { return isClear; }

	// 終了フラグ
	bool ClearFinished_ = false;
	bool DeadFinished_ = false;

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Model* cubeModel_;

	Model* PlayerModel_;
	Model* playerBulletModel_;

	Model* longModel_;
	Model* shortModel;
	Model* flyModel;

	//////////////////////////////
	// Enemy
	Model* enemyModel_;
	ActorManager* actorManager_;
	/*std::shared_ptr<EnemyActor> Enemy_;*/
	// std::list<std::shared_ptr<EnemyActor>> Enemy;
	// EnemyManager* enemy_;

	//////////////////////////////

	Model* skyDome_;
	Model* ground_;

	WorldTransform skyDomeTrans;

	ActorManager* actorManager;

	
};
