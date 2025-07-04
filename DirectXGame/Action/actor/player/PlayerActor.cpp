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

	objectColor = new ObjectColor;
	objectColor->Initialize();
}

void PlayerActor::Update() {

	XInputGetState(0, &xinput_);

	if (hitCoolDown > 0.0f)
	{
		hitCoolDown -= flameTime_;
	}

	// 左スティックのX, Y値を取得
	lx = xinput_.Gamepad.sThumbLX / 32767.0f; // 正規化（-1.0 ～ 1.0）
	ly = xinput_.Gamepad.sThumbLY / 32767.0f;

	Move();

	Attack();

	// ジャンプ中の処理
	if (isJumping_) {
		worldTransform_.translation_.y += jumpSpeed_;
		jumpSpeed_ += kGravity;

		// 地面に着地した場合
		if (worldTransform_.translation_.y <= kGroundHeight) {
			worldTransform_.translation_.y = kGroundHeight;
			isJumping_ = false;
			jumpSpeed_ = 0.0f;
			onGround_ = true;
		}
	}

	move_ = Normalize(move_) * kSpeed_;

	Matrix4x4 matRot = MakeRotateYMatrix(cameraRot_.y);
	
	move_ = TransformNormal(move_, matRot);

	if (isDush_)
	{
		move_ *= dushSpeed_;
	}

	worldTransform_.translation_ += move_;

	UpdateDirectionBasedOnMovement();

	DrawImGui();

	move_ = Vector3{0.0f, 0.0f, 0.0f};

	worldTransform_.UpdateMatrix();
}

void PlayerActor::Draw(Camera& camera) { 

	if (hitCoolDown < 1.0f)
	{
		color.w = 0.8f;
	} else
	{
		color.w = 1.0f;
	}
	objectColor->SetColor(color);

	model_->Draw(worldTransform_, camera, objectColor);
}

void PlayerActor::UpdateDirectionBasedOnMovement()
{

	// 移動入力がある場合に向きを変更
	if (move_.x != 0.0f || move_.z != 0.0f) {
		float angle = atan2(move_.x, move_.z);
		worldTransform_.rotation_.y = angle;
	}
}

void PlayerActor::DrawImGui() {
	#ifdef  _DEBUG
	ImGui::Begin("player");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("move", &move_.x, 0.1f);
	ImGui::DragFloat3("cameraRot", &cameraRot_.x, 0.1f);
	ImGui::DragFloat("hit", &hitCoolDown, 0.1f);
	ImGui::DragInt("HP", &hp);
	ImGui::End();
	#endif
}