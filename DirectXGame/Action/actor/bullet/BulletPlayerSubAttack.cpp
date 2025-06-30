#include "BulletPlayerSubAttack.h"

using namespace MathUtility;

BulletPlayerSubAttack::BulletPlayerSubAttack()
{
	damage_ = 2;
}

void BulletPlayerSubAttack::Move()
{
	if (!start_)
	{
		start_ = true;

	}

	DeleteTimerCheck();
}
