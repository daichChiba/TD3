#include "BulletPlayerSubAttack.h"

using namespace MathUtility;

void BulletPlayerSubAttack::Move()
{
	if (start_)
	{
		move_ *= speed_;
		start_ = false;

	}

	DeleteTimerCheck();
}
