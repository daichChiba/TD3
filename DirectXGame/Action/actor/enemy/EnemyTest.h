#pragma once
#include "kamataEngine.h"
#include "EnemyActor.h"
using namespace KamataEngine;


class EnemyTest : public EnemyActor {
public:
	EnemyTest();
	~EnemyTest();

private:
	void Move() override;
	void Attack() override;

};
