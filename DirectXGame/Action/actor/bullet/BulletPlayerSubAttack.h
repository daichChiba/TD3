#pragma once
#include "BulletActor.h"

#include "KamataEngine.h"

using namespace KamataEngine;

class BulletPlayerSubAttack : public BulletActor
{
public:
	BulletPlayerSubAttack();

private:
	void Move() override;
	
	bool start_ = false;

	float speed_ = 1.0f;
	
};

