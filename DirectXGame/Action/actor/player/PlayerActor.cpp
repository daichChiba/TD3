#include "PlayerActor.h"

#include "../ActorManager.h"

using namespace MathUtility;

void PlayerActor::Initialize(Model* model, Model* bulletModel, const Vector3 pos, ActorManager* actorManager) {
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;
	BulletModel_ = bulletModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	actorManager_ = actorManager;

	//camera_ = actorManager_ ->SetCamera();
}

void PlayerActor::Update() {
	Move();

	Attack();

	move_ = Normalize(move_) * kSpeed_;

	if (camera_) {
		/*float cameraYawY = camera_->rotation_.y;
		float s = sin(cameraYawY);
		float c = cos(cameraYawY);

		float newX = move_.x * c - move_.z * s;
		float newZ = move_.x * s + move_.z * c;

		move_.x = newX;
		move_.z = newZ;*/

		Matrix4x4 matRotX = MakeRotateXMatrix(camera_->rotation_.x);
		Matrix4x4 matRotY = MakeRotateYMatrix(camera_->rotation_.y);
		Matrix4x4 matRotZ = MakeRotateZMatrix(camera_->rotation_.z);

		Matrix4x4 matRot = matRotX * matRotY * matRotZ;

		move_ = TransformNormal(move_, matRot);

		move_.y = 0.0f;
    }

	

	worldTransform_.translation_ += move_;
	DrawImGui();
	move_ = Vector3{0.0f, 0.0f, 0.0f};

	worldTransform_.UpdateMatrix();
	
}

void PlayerActor::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }

void PlayerActor::DrawImGui() {
	ImGui::Begin("player");
	ImGui::Text("pos : %.3f,%.3f,%.3f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::Text("rot : %.3f,%.3f,%.3f", worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z);
	ImGui::Text("move : %.3f,%.3f,%.3f", move_.x, move_.y, move_.z);
	ImGui::Text("cameraRot : %.3f,%.3f,%.3f", camera_->rotation_.x, camera_->rotation_.y, camera_->rotation_.z);
	ImGui::Text("a : %d", a);
	ImGui::End();
}