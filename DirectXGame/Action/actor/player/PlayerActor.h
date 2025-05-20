#pragma once

#include "KamataEngine.h"

using namespace KamataEngine;

class ActorManager;

class PlayerActor {
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

	void UpdateDirectionBasedOnMovement();

	void DrawImGui();

	WorldTransform* GetWorldTransfrom() { return &worldTransform_; }

	float GetRadius() { return radius_; }
	void OnCollision(){
		hp--;
		hitCoolDown  = 1.0f;
	}

	bool IsHitCoolDown() {

		bool result = false;
		if (hitCoolDown <= 0.0f)
		{
	
			result = true;
		}
		return result;
	}

	int hp = 10;

	void SetCameraRot(Vector3 cameraRot) { cameraRot_ = cameraRot; }

protected:
	virtual void Move() { return; }
	virtual void Attack() { return; }

	Model* model_;
	Model* BulletModel_;
	WorldTransform worldTransform_;

	Vector3 cameraRot_;

	float radius_ = 1.0f;


	ActorManager* actorManager_;

	XINPUT_STATE xinput_;
	float lx, ly;

	static inline const float flameTime_ = 1.0f / 60.0f;

	

	float hitCoolDown = 3.0f;

	Vector3 move_;
	static inline const float kSpeed_ = 0.3f;
	
	bool isDush_ = false;
	float dushSpeed_ = 0.0f;
	static inline const float kDushForce = 20.0f;


};
