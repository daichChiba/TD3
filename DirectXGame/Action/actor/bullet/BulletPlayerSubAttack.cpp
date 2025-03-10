#include "BulletPlayerSubAttack.h"

using namespace MathUtility;

void BulletPlayerSubAttack::Move()
{
	if (start_)
	{
		move_ *= speed_;
		start_ = false;
	}
	deleteTimer_ -= 1.0f / 60.0f;
}
