#pragma once
#include "BulletActor.h"
class BulletFlyEnemy :
    public BulletActor
{

private:
    void Move() override;
    void Attack() override {};
};

