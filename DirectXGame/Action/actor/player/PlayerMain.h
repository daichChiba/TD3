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

	static inline const float PlayerMoveSpeed = 0.05f;
};