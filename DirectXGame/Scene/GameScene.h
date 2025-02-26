#pragma once
#include <KamataEngine.h>
#include "../Action/actor/ActorManager.h"

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

	private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Model* cubeModel_;

	Model* PlayerModel_;
	Model* playerBulletModel_;

	Model* skyDome_;

	WorldTransform skyDomeTrans;

	ActorManager* actorManager;
};
