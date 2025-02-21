#include "PlayerActor.h"

void PlayerActor::Initialize(Model* model, Model* bulletModel, const Vector3 pos)
{
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;
	BulletModel_ = bulletModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void PlayerActor::Update()
{
	worldTransform_.UpdateMatrix();
}

void PlayerActor::Draw(Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}
