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
	void OnCollision(){ return;}

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

	Vector3 move_;
	static inline const float kSpeed_ = 0.3f;

	float playerYSpeed;

	bool onGround_;
	static inline const float kGroundHeight = 0.5f;
	static inline const float kGravity = -0.03f;

	bool isJumping_ = true;
	float jumpSpeed_ = 0.0f;
	static inline const float kJumpForce = 0.5f;
	
	bool isDush_ = false;
	float dushSpeed_ = 0.0f;
	static inline const float kDushForce = 20.0f;
};
