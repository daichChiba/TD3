#pragma once
#include "KamataEngine.h"

#include "EnemyActor.h"

class EnemyBoss : public EnemyActor
{

private:
	void Move() override;

	void Attack() override;

	float time = 0.0f;

	void MoveToPlayer();



	void DashAttack();
	
	void bounceAttack();

	void ShootCircle();

	void ShootRaser();
};

