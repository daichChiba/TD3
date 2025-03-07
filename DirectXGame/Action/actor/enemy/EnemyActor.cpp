#include "EnemyActor.h"
using namespace MathUtility;

void EnemyActor::Initialize(Model* model, Model* bulletModel, const Vector3 pos, ActorManager* actorManager) {
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif

	model_ = model;
	BulletModel_ = bulletModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	actorManager_ = actorManager;

	move_ = Vector3{0.0f, 0.0f, 0.0f};
}

void EnemyActor::Update() {
	Move();
	Attack();

	worldTransform_.translation_ += move_;

	DrawImGui();

	worldTransform_.UpdateMatrix();
}

void EnemyActor::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }

void EnemyActor::DrawImGui() {
	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
	ImGui::Text("move : %.3f,%.3f,%.3f", move_.x, move_.y, move_.z);
	ImGui::End();
}
