#pragma once

#include "KamataEngine.h"

using namespace KamataEngine;

class ActorManager;

class EnemyActor {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">モデルの座標</param>
	void Initialize(Model* model, Model* bulletModel, const Vector3 pos, ActorManager* actorManager);

	/// <summary>
	/// アップデート
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera& camera);


	void DrawImGui();

	WorldTransform* GetWorldTransfrom() { return &worldTransform_; }

	void SetMove(Vector3 move) { move_ = move; }

	


// このクラスと派生クラスでしか使わない関数はprotectedにする
protected:
	virtual void Move() { return; }
	virtual void Attack() { return; }

	Model* model_;
	Model* BulletModel_;
	WorldTransform worldTransform_;

	ActorManager* actorManager_;

	Vector3 move_;
	static inline const float kSpeed_ = 0.3f;

};
