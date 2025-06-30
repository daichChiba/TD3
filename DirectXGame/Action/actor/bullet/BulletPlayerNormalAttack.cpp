#include "BulletPlayerNormalAttack.h"

void BulletPlayerNormalAttack::Move()
{
	if(!isStart_)
	{
		isStart_ = true;
	}
	DeleteTimerCheck();
}

void BulletPlayerNormalAttack::DeleteTimerCheck()
{


	if (deleteTimer_ > kDeleteTime_)
	{
		isDelete_ = true;
	}
}
