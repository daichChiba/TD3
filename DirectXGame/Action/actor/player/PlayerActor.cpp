#include "PlayerActor.h"

using namespace MathUtility;

void PlayerActor::Initialize(Model* model, Model* bulletModel, const Vector3 pos) {
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;
	BulletModel_ = bulletModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void PlayerActor::Update() {
	Move();

	Attack();

	move_ = Normalize(move_) * kSpeed_;

	if (camera_) {
		float cameraYaw = camera_->rotation_.y;
		float s = sin(cameraYaw);
		float c = cos(cameraYaw);

		float newX = move_.x * c - move_.z * s;
		float newZ = move_.x * s + move_.z * c;

		move_.x = newX;
		move_.z = newZ;

    }

	

	worldTransform_.translation_ += move_;
	move_ = Vector3{0.0f, 0.0f, 0.0f};

	worldTransform_.UpdateMatrix();
	DrawImGui();
}

void PlayerActor::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }

void PlayerActor::DrawImGui() {
	ImGui::Begin("player");
	ImGui::Text("pos : %.3f,%.3f,%.3f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::Text("rot : %.3f,%.3f,%.3f", worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z);
	ImGui::End();
}