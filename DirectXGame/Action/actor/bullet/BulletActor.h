#pragma once

#include "KamataEngine.h"

using namespace KamataEngine;

class BulletActor
{
public:
	void Initialize(Model* model, Vector3 pos);
	void Update();
	virtual void Draw(Camera& camera);

	void SetScale( Vector3 scale){ worldTransform_.scale_ = scale; }
	void SetMove( Vector3 MoveVectorl){ move_ = MoveVectorl; }
	
	bool IsDelete() const { return isDelete_; }

	virtual void OnCollision();
	float GetRadius() { return worldTransform_.scale_.x * radius_; }
protected:
	virtual void Move();
	virtual void DeleteTimerCheck();

	Model* model_ = nullptr;
	WorldTransform worldTransform_;

	Vector3 move_;

	bool isDelete_ = false;
	float deleteTimer_;
	static inline const float kDeleteDefaltTime_ = 5.0f;

	float radius_ = 1.0f;

	ObjectColor* color = nullptr;
};