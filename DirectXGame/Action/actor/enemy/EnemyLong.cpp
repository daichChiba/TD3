#include "EnemyLong.h"
using namespace MathUtility;


EnemyLong::EnemyLong() {
	// 最初の位置
	enemyStartPos = {1.0f, 1.0f, 15.0f};
	
	hp = enemy_hp_;

	// プレイヤーとの距離を測る変数
	distanceToPlayer_ = 1.0f;
}

EnemyLong::~EnemyLong() {}

void EnemyLong::Move() {
	ApproachPlayer();
	worldTransform_.translation_ += move_;
}

void EnemyLong::Attack() {}