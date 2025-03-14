#pragma once
#include "BulletActor.h"
class BulletPlayerNormalAttack :
    public BulletActor
{
private:
    void Move() override;
    void DeleteTimerCheck() override;

    bool isStart_ = false;

    static inline const float kDeleteTime_ = 0.3f;
};
