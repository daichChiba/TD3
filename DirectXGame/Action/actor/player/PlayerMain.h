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

	Vector3 acceletion;

	static inline const float kMpoveSpeed = 0.1f;
	static inline const float kJumpPower = 1.0f;
	static inline const float kAttenuation = 0.1f;

	static inline const float deadZone = 0.1f;
};