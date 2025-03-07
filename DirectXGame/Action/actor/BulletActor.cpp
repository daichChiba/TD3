#include "BulletActor.h"

using namespace MathUtility;

void BulletActor::Initialize(Model* model, Vector3 pos)
{
#ifdef _DEBUG
	assert(model);
#endif // _DEBUG

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	color = new ObjectColor;
	color->Initialize();
	color->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
}

void BulletActor::Update()
{
	Move();

	worldTransform_.translation_ += velocity_;
	worldTransform_.UpdateMatrix();
}

void BulletActor::Draw(Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}

void BulletActor::OnCollision()
{
	isDelete_ = true;
}

void BulletActor::Move()
{
	deleteTimer_ += 60.0f/ 1.0f;
	if (deleteTimer_ > kDeleteTime_)
	{
		isDelete_ = true;
	}
}
