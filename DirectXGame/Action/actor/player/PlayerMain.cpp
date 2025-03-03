#include "PlayerMain.h"

using namespace MathUtility;

PlayerMain::PlayerMain() {}

PlayerMain::~PlayerMain() {}

void PlayerMain::Move() {

	
	acceletion = Vector3Zero();
	if (Input::GetInstance()->PushKey(DIK_W) || Input::GetInstance()->PushKey(DIK_UP)) {
		acceletion.z += kMpoveSpeed;
		
	} else if (Input::GetInstance()->PushKey(DIK_S) || Input::GetInstance()->PushKey(DIK_DOWN)) {
		acceletion.z += -kMpoveSpeed;
	
	} else {
		acceletion.z = 0.0f;
	}
	if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		acceletion.x += -kMpoveSpeed;
		
	} else if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_RIGHT)) {
		acceletion.x += kMpoveSpeed;
		
	} else {
		acceletion.x;
	}

	if (Input::GetInstance()->PushKey(DIK_SPACE) && onGround_ == true) {
		move_.y = kJumpPower;
		onGround_ = false;
	}

	move_ += acceletion;

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
