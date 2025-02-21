#pragma once
#include <KamataEngine.h>
#include "../action/actor/player/PlayerActor.h"
#include "../action/actor/player/PlayerMain.h"

using namespace KamataEngine;


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

	Camera* camera;

	Model* PlayerModel_;
	Model* playerBulletModel_;

	PlayerActor* Player_;
};
