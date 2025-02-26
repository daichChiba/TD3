#include "FolloCamera.h"

using namespace MathUtility;

void FollowCamera::Initialize()
{
	followCamera.Initialize();
}

void FollowCamera::Update()
{
	XInputGetState(0, &xinput_);

	if (target_) {
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		 Matrix4x4 rotationMatrix = MakeRotateYMatrix(followCamera.rotation_.y);

		offset = TransformNormal(offset, rotationMatrix);
		
		followCamera.translation_ = target_->translation_ + offset;
	}

	float Rx = xinput_.Gamepad.sThumbRX / 32767.0f; // 正規化（-1.0 ～ 1.0）
	//float Ry = xinput_.Gamepad.sThumbRY / 32767.0f;

	if(Rx >= 0.8f)
	{
		// カメラの回転を更新
		followCamera.rotation_.y += Rx * kRotationSpeed;
	}
	else if (Input::GetInstance()->PushKey(DIK_Q))
	{
		followCamera.rotation_.y -= kRotationSpeed;
	}
	else if (Input::GetInstance()->PushKey(DIK_E))
	{
		followCamera.rotation_.y += kRotationSpeed;
	}

	followCamera.UpdateMatrix();
	DrowImgui();
}

void FollowCamera::DrowImgui()
{
	ImGui::Begin("followCamera");
	ImGui::Text("pos : %.3f,%.3f,%.3f", followCamera.translation_.x,followCamera.translation_.y,followCamera.translation_.z);
	ImGui::Text("rot : %.3f,%.3f,%.3f", followCamera.rotation_.x, followCamera.rotation_.y ,followCamera.rotation_.z);
	ImGui::End();
}
