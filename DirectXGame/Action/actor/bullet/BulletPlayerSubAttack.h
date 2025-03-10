#pragma once
#include "BulletActor.h"

#include "KamataEngine.h"

using namespace KamataEngine;

class BulletPlayerSubAttack : public BulletActor
{
public:
	

private:
	void Move() override;
	
	bool start_ = true;

	float speed_ = 1.0f;
};

