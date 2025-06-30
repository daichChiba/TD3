#include "PlayerMain.h"


#include "../ActorManager.h"

#include "../bullet/BulletActor.h"
#include "../bullet/BulletPlayerSubAttack.h"
#include "../bullet/BulletPlayerNormalAttack.h"


using namespace MathUtility;

PlayerMain::PlayerMain() {}

PlayerMain::~PlayerMain() {}

void PlayerMain::Move() {

	CheckKey();
	SkillTimerMove();

	if (lx <= -deadZone || lx >= deadZone || ly <= -deadZone || ly >= deadZone) {
		// デッドゾーンの設定(スティックがニュートラルに近い場合に意図せず移動しないようにする)
		if (fabs(lx) < deadZone)
			lx = 0.0f;
		if (fabs(ly) < deadZone)
			ly = 0.0f;

		// スティックの強度と角度を計算
		float magnitude = sqrtf(lx * lx + ly * ly); // 入力強度（0 ～ 1）
		float angle = atan2f(ly, lx);               // スティックの角度（ラジアン）

		move_.x = cos(angle) * magnitude * kAcceletion;
		move_.z = sin(angle) * magnitude * kAcceletion;
	} else {
		acceletion = Vector3Zero();
		if (previousKey || backKey) {
			if (previousKey) {
				if (move_.z < 0.0f)
					move_.z *= (1.0f - kAttenuation);

				acceletion.z += kAcceletion;

			} else if (backKey) {
				if (move_.z > 0.0f)
					move_.z *= (1.0f - kAttenuation);

				acceletion.z += -kAcceletion;
			}
		} else {
			move_.z *= (1.0f - kAttenuation);
			// move_.z = 0.0f;
			if (std::abs(move_.z) < moveRiset)
				move_.z = 0.0f;
		}

		if (rightKey || leftKey) {
			if (leftKey) {
				if (move_.x < 0.0f)
					move_.x *= (1.0f - kAttenuation);
				acceletion.x += -kAcceletion;
			} else if (rightKey) {
				if (move_.x > 0.0f)
					move_.x *= (1.0f - kAttenuation);
				acceletion.x += kAcceletion;
			}
		} else {
			move_.x *= (1.0f - kAttenuation);

			if (std::abs(move_.x) < moveRiset)
				move_.x = 0.0f;
		}
	}

	// ジャンプの入力を検出
	if (jumpKey && onGround_) {
		isJumping_ = true;
		jumpSpeed_ = kJumpForce;
		onGround_ = false;
	}

	if (dushKey && dushTimer_ < 0.0f)
	{
		isDush_ =  true;
		dushSpeed_ = kDushForce;
		dushTimer_ = kDushCoolTime_;
	}
	if (dushSpeed_ < 1.0f)
	{
		isDush_ =  false;
	}

	move_ += acceletion;
	dushSpeed_ -= 0.8f;

#ifdef _DEBUG
	ImGui::Begin("PlayerMain");
	ImGui::DragFloat3("playerAcceletion", &acceletion.x, 0.01f);
	ImGui::DragFloat3("playermove", &move_.x, 0.01f);
	ImGui::DragFloat("playerdush", &dushSpeed_, 0.01f);
	ImGui::End();
#endif // _DEBUG
}

void PlayerMain::Attack() {
	if(normalAttackKey && normalAttackTimer_ < 0.0f){
		std::shared_ptr<BulletActor> attack = std::make_shared<BulletPlayerNormalAttack>();
		attack->Initialize(BulletModel_, worldTransform_.translation_);
		
		Vector3 forward = GetCameraForward();
		forward *= 0.5f;
		attack->SetMove(forward); // bulletSpeed は弾の速度

		attack->SetScale(Vector3( 0.5f, 0.5f, 0.5f));
		
		actorManager_->AddBullet(attack); // プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す

		
		worldTransform_.rotation_.y = cameraRot_.y;

		normalAttackTimer_ = kNormalAttackCoolTime_;
		actionLockTimer_ = kActionLockCoolTime_;

	}

	if(subAttackKey && subAttackTimer_ < 0.0f){
		std::shared_ptr<BulletActor> attack = std::make_shared<BulletPlayerSubAttack>();
		attack->Initialize(BulletModel_, worldTransform_.translation_);
		
		Vector3 forward = GetCameraForward();
        attack->SetMove(forward); // bulletSpeed は弾の速度

		actorManager_->AddBullet(attack); // プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す

		subAttackTimer_ = kSubAttackCoolTime_;
	}

	if (actionLockTimer_ > 0.0f)
	{
		move_.x = 0.0f;
		move_.z = 0.0f;
	}
}

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
	if (xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_A || Input::GetInstance()->PushKey(DIK_SPACE)) {
		jumpKey = true;
	} else {
		jumpKey = false;
	}
	if (xinput_.Gamepad.wButtons & XINPUT_GAMEPAD_B || Input::GetInstance()->PushKey(DIK_LSHIFT)) {
		dushKey = true;
	} else {
		dushKey = false;
	}
	if (xinput_.Gamepad.bRightTrigger >= 100 || Input::GetInstance()->PushKey(DIK_Q) || Input::GetInstance()->IsTriggerMouse(0)) {
		normalAttackKey = true;
	} else {
		normalAttackKey = false;
	}
	if (xinput_.Gamepad.bLeftTrigger >= 100 || Input::GetInstance()->PushKey(DIK_E) || Input::GetInstance()->IsTriggerMouse(1)) {
		subAttackKey = true;
	} else {
		subAttackKey = false;
	}
}

void PlayerMain::SkillTimerMove()
{
	dushTimer_ -= flameTime_;
	normalAttackTimer_ -= flameTime_;
	subAttackTimer_ -= flameTime_;
	actionLockTimer_ -= flameTime_;
}

inline Vector3 PlayerMain::GetCameraForward() const {
	// カメラの回転情報を取得
    float yaw = cameraRot_.y;
    float pitch = cameraRot_.x;

    // 前方ベクトルを計算
    Vector3 forward;
    forward.x = sin(yaw) * cos(pitch);
    forward.y = sin(-pitch);
    forward.z = cos(yaw) * cos(pitch);

    return forward;
}
