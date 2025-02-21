#pragma once

#include "KamataEngine.h"

using namespace KamataEngine;

class GameScene;

class PlayerActor {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">モデルの座標</param>
	void Initialize(Model* model, Model* bulletModel, const Vector3 pos);

	/// <summary>
	/// アップデート
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera& camera);

private:
	Model* model_;
	Model* BulletModel_;
	WorldTransform worldTransform_;
};
