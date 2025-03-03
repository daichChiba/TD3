#include "PlayerMain.h"

using namespace MathUtility;

PlayerMain::PlayerMain() {}

PlayerMain::~PlayerMain() {}

void PlayerMain::Move() {

	CheckKey();

	acceletion = Vector3Zero();
	if (previousKey || backKey) {
		if (previousKey) {
			if (move_.z < 0.0f)
				move_.z *= (1.0f - kAttenuation);

			acceletion.z += kMpoveSpeed;
			a = 1;

		} else if (backKey) {
			if (move_.z > 0.0f)
				move_.z *= (1.0f - kAttenuation);

			acceletion.z += -kMpoveSpeed;
			a = 1;
		}
	} else {
		move_.z *= (1.0f - kAttenuation);
		//move_.z = 0.0f;
		if (std::abs(move_.z) < moveRiset && a == 1)
			move_.z = 0.0f;
			a = 0;
	}

	if (rightKey || leftKey) {
		if (leftKey) {
			if (move_.x < 0.0f)
				move_.x *= (1.0f - kAttenuation);
			acceletion.x += -kMpoveSpeed;
		} else if (rightKey) {
			if (move_.x > 0.0f)
				move_.x *= (1.0f - kAttenuation);
			acceletion.x += kMpoveSpeed;
		}

	} else {
		move_.x *= (1.0f - kAttenuation);
		//move_.x = 0.0f;
		if (std::abs(move_.x) < moveRiset)
			move_.x = 0.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_SPACE) && onGround_ == true) {
		move_.y = kJumpPower;
		onGround_ = false;
	}

	move_ += acceletion;

	ImGui::Begin("PlayerMain");
	ImGui::DragFloat3("playerAcceletion", &acceletion.x, 0.01f);
	ImGui::DragFloat3("playermove", &move_.x, 0.01f);
	ImGui::End();

	if (lx <= -deadZone || lx >= deadZone || ly <= -deadZone || ly >= deadZone) {
		// デッドゾーンの設定(スティックがニュートラルに近い場合に意図せず移動しないようにする)
		if (fabs(lx) < deadZone)
			lx = 0.0f;
		if (fabs(ly) < deadZone)
			ly = 0.0f;

		// スティックの強度と角度を計算
		float magnitude = sqrtf(lx * lx + ly * ly); // 入力強度（0 ～ 1）
		float angle = atan2f(ly, lx);               // スティックの角度（ラジアン）

		move_.x = cos(angle) * magnitude;
		move_.z = sin(angle) * magnitude;
	}

	
}

void PlayerMain::Attack() {}

void PlayerMain::CheckKey() {
	if (Input::GetInstance()->PushKey(DIK_W) || Input::GetInstance()->PushKey(DIK_UP)) {
		previousKey = true;
	} else {
		previousKey = false;
	}
	if (Input::GetInstance()->PushKey(DIK_S) || Input::GetInstance()->PushKey(DIK_DOWN)) {
		backKey = true;
	} else {
		backKey = false;
	}
	if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		leftKey = true;
	} else {
		leftKey = false;
	}
	if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_RIGHT)) {
		rightKey = true;
	} else {
		rightKey = false;
	}
}
