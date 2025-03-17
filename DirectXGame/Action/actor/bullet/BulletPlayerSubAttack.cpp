#include "BulletPlayerSubAttack.h"

using namespace MathUtility;

void BulletPlayerSubAttack::Move()
{
	if (!start_)
	{
		start_ = true;

	}

	DeleteTimerCheck();
}
