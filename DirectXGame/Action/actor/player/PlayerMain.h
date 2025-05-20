#pragma once
#include "KamataEngine.h"
#include "PlayerActor.h"

using namespace KamataEngine;

class PlayerMain : public PlayerActor
{
public:
	PlayerMain();
	~PlayerMain();

private:
	
	void Move() override;
	void Attack() override;

	void CheckKey();

	void SkillTimerMove();

	Vector3 GetCameraForward() const;

	Vector3 acceletion;

	static inline const float kAcceletion = 0.3f;
	static inline const float kAttenuation = 0.05f;

	static inline const float moveRiset = 0.01f;
	static inline const float deadZone = 0.1f;

#pragma region スキルクールタイム
	float kDushCoolTime_ = 2.0f;
	float kNormalAttackCoolTime_ = 1.4f;
	float kActionLockCoolTime_ = 0.2f;
	float kSubAttackCoolTime_ = 0.5f;
#pragma endregion

#pragma region スキルタイマー
	float dushTimer_ = 0.0f;
	float normalAttackTimer_ = 0.0f;
	float actionLockTimer_ = 0.0f;
	float subAttackTimer_ = 0.0f;
#pragma endregion  

#pragma region キーチェック
	bool previousKey;
	bool backKey;
	bool rightKey;
	bool leftKey;
	bool dushKey;
	bool normalAttackKey;
	bool subAttackKey;
#pragma endregion
};