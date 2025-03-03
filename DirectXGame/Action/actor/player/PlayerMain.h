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

	Vector3 acceletion;

	int a = 0;

	static inline const float kMpoveSpeed = 0.1f;
	static inline const float kJumpPower = 1.0f;
	static inline const float kAttenuation = 0.05f;

	static inline const float moveRiset = 1.0f;
	static inline const float deadZone = 0.1f;

	bool previousKey;
	bool backKey;
	bool rightKey;
	bool leftKey;
};