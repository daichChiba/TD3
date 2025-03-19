#include "EnemyFly.h"

EnemyFly::EnemyFly(){
	enemyStartPos = {1.0f, 3.0f, 1.0f};
	minDistanceY_ = 5.0f;
}

EnemyFly::~EnemyFly() {}

void EnemyFly::Move() {
	ApproachPlayer();
}

void EnemyFly::Attack() {
	// 攻撃のコード
}