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

	Vector3 acceletion;

	static inline const float kAcceletion = 0.3f;
	static inline const float kJumpPower = 3.0f;
	static inline const float kAttenuation = 0.05f;

	static inline const float moveRiset = 0.01f;
	static inline const float deadZone = 0.1f;

#pragma region スキルクールタイム
	float kNormalAttackCoolTime_ = 0.8f;
	float kSubAttackCoolTime_ = 0.1f;
#pragma endregion

#pragma region スキルタイマー
	float NormalAttackTimer_ = 0.0f;
	float SubAttackTimer_ = 0.0f;
#pragma endregion  

	bool previousKey;
	bool backKey;
	bool rightKey;
	bool leftKey;
	bool jumpKey;
	bool normalAttackKey;
};