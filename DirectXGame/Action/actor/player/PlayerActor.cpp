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
}

void PlayerActor::Update() {

	XInputGetState(0, &xinput_);

	// 左スティックのX, Y値を取得
	lx = xinput_.Gamepad.sThumbLX / 32767.0f; // 正規化（-1.0 ～ 1.0）
	ly = xinput_.Gamepad.sThumbLY / 32767.0f;

	if (worldTransform_.translation_.y > kGroundHeight) {
		worldTransform_.translation_.y += kFoalSpeed;
	}
	if (worldTransform_.translation_.y < kGroundHeight) {
		worldTransform_.translation_.y = kGroundHeight;
		onGround_ = true;
	}

	Move();

	Attack();

	
	//move_ = move_ * kSpeed_;
	//move_ = Normalize(move_);

	Matrix4x4 matRotX = MakeRotateXMatrix(cameraRot_.x);
	Matrix4x4 matRotY = MakeRotateYMatrix(cameraRot_.y);
	Matrix4x4 matRotZ = MakeRotateZMatrix(cameraRot_.z);

	Matrix4x4 matRot = matRotX * matRotY * matRotZ;

	//move_ = TransformNormal(move_, matRot);

	worldTransform_.translation_ += move_;

	DrawImGui();
	move_ = Vector3{0.0f, 0.0f, 0.0f};

	worldTransform_.UpdateMatrix();
}

void PlayerActor::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }

void PlayerActor::DrawImGui() {
	ImGui::Begin("player");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("move", &move_.x, 0.1f);
	ImGui::DragFloat3("cameraRot", &cameraRot_.x, 0.1f);
	ImGui::End();
}