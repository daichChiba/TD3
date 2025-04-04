#include "BulletActor.h"

#include "../ActorManager.h"

using namespace MathUtility;

void BulletActor::Initialize(Model* model, Vector3 pos)
{
#ifdef _DEBUG
	assert(model);
#endif // _DEBUG

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	isDelete_ = false;

	color = new ObjectColor;
	color->Initialize();
	color->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
}

void BulletActor::Update()
{
	deleteTimer_ += 1.0f / 60.0f;

	Move();

	worldTransform_.translation_ += move_;
	
	if (worldTransform_.translation_.y < -3.0f)
	{
		isDelete_= true;
	}
#ifdef  _DEBUG
	ImGui::Begin("bullet");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
	ImGui::DragFloat3("move", &move_.x);
	ImGui::Text("deleteTimer : %.2f", deleteTimer_);
	ImGui::End();
#endif
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

void BulletActor::SetACManager(ActorManager* acManager)
{
	actorManager_ = acManager;
}

void BulletActor::Move()
{
	
}

void BulletActor::DeleteTimerCheck()
{
	if (deleteTimer_ > kDeleteDefaltTime_)
	{
		isDelete_ = true;
	}
}
