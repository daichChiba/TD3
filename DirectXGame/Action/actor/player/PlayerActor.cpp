#include "PlayerActor.h"

using namespace MathUtility;

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
	Move();

	Attack();

	worldTransform_.translation_ += velocity;
	velocity = Vector3{ 0.0f, 0.0f, 0.0f};

	worldTransform_.UpdateMatrix();
}

void PlayerActor::Draw(Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}
