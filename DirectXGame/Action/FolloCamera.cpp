#include "FolloCamera.h"

using namespace MathUtility;

void FollowCamera::Initialize() { followCamera.Initialize(); }

void FollowCamera::Update() {
	XInputGetState(0, &xinput_);

	moveCameraRotateXAdd = true;
	moveCameraRotateXLower = true;

	if (target_) {
		offset_ = {0.0f, 2.0f, -10.0f};

		Matrix4x4 rotationXMatrix = MakeRotateXMatrix(followCamera.rotation_.x);
		Matrix4x4 rotationYMatrix = MakeRotateYMatrix(followCamera.rotation_.y);
		//Matrix4x4 rotationZMatrix = MakeRotateYMatrix(followCamera.rotation_.z);

		Matrix4x4 rotationMatrix = rotationXMatrix * rotationYMatrix;

		offset_ = TransformNormal(offset_, rotationMatrix);

		followCamera.translation_ = target_->translation_ + offset_;
	}

	if (followCamera.translation_.y < kMinCameraHeight)
	{
		moveCameraRotateXAdd = false;
	}
	if (followCamera.translation_.y > kMaxCameraHeight)
	{
		moveCameraRotateXLower = false;
	}

	Rx = xinput_.Gamepad.sThumbRX / 32767.0f; // 正規化（-1.0 ～ 1.0）
	Ry = xinput_.Gamepad.sThumbRY / 32767.0f;

	if (Rx >= kDeadZone || Rx <= -kDeadZone || Ry >= kDeadZone || Ry <= -kDeadZone) {
		// カメラの回転を更新
		followCamera.rotation_.y -= Rx * kRotationSpeed;
		if(moveCameraRotateXAdd && Ry < 0.0f)
			followCamera.rotation_.x += Ry * kRotationSpeed;
		if(moveCameraRotateXLower && Ry > 0.0f)
			followCamera.rotation_.x += Ry * kRotationSpeed;
	} 
	else if (Input::GetInstance()->PushKey(DIK_J)) {
		followCamera.rotation_.y -= kRotationSpeed;
	} else if (Input::GetInstance()->PushKey(DIK_L)) {
		followCamera.rotation_.y += kRotationSpeed;
	}
	else if (Input::GetInstance()->PushKey(DIK_I)) {
		
		if(moveCameraRotateXLower)
		followCamera.rotation_.x += kRotationSpeed;
	}
	else if (Input::GetInstance()->PushKey(DIK_K)) {
		if (moveCameraRotateXAdd)
		followCamera.rotation_.x -= kRotationSpeed;
		
	} 

	if (followCamera.rotation_.y > 6.28f || followCamera.rotation_.y < -6.28f)
	{
		followCamera.rotation_.y = 0.0f;
	}

	followCamera.UpdateViewMatrix();
}

void FollowCamera::DrawImgui() {
	ImGui::Begin("followCamera");
	ImGui::DragFloat3("pos", &followCamera.translation_.x);
	ImGui::DragFloat3("rot", &followCamera.rotation_.x);
	ImGui::DragFloat3("offset", &offset_.x);
	ImGui::End();
	// followCamera.UpdateViewMatrix();
}

void FollowCamera::DrowImgui() {
	ImGui::Begin("followCamera");
	ImGui::Text("pos : %.3f,%.3f,%.3f", followCamera.translation_.x, followCamera.translation_.y, followCamera.translation_.z);
	ImGui::Text("rot : %.3f,%.3f,%.3f", followCamera.rotation_.x, followCamera.rotation_.y, followCamera.rotation_.z);
	ImGui::Text("conX : %f", Rx);

	ImGui::End();
}
