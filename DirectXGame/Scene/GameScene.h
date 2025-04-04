#pragma once
#include <KamataEngine.h>
#include "../Action/actor/ActorManager.h"

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

	// デスフラグのgetter
	bool IsStop() const { return isStop; }
	void SetIsStop() { isStop = !isStop; }
	bool IsFinished() const { return isEnd; }
	bool IsClear() const { return isClear; }


private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Model* cubeModel_;

	Model* PlayerModel_;
	Model* playerBulletModel_;

	uint32_t scopeTtexture;
	Sprite* playerScpoeSprite;

	Model* longModel_;
	Model* shortModel;
	Model* flyModel;

	//////////////////////////////
	// Enemy
	Model* enemyModel_;
	Model* enemyBullet_;
	/*std::shared_ptr<EnemyActor> Enemy_;*/
	//std::list<std::shared_ptr<EnemyActor>> Enemy;
	//EnemyManager* enemy_;

	//////////////////////////////

	Model* skyDome_;
	Model* ground_;

	WorldTransform skyDomeTrans;

	ActorManager* actorManager;

	Vector2 scopePos = {600.0f, 350.0f};

	bool isStop = false;
	bool isEnd = false;
	bool isClear = false;
};
