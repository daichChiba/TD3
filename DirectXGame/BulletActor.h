#pragma once

#include "KamataEngine.h"

using namespace KamataEngine;

class ActorManager;

class BulletActor
{
public:
	void Initialize(Model* model, Vector3 pos);
	void Update();
	void Draw(Camera* camera);

	void SetActor(ActorManager* actor);
	
	virtual void OnCollision();
protected:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;

	Vector3 velocity_;

	bool isDelete_ = false;
};
