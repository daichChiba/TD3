#include "EnemyShort.h"
using namespace MathUtility;


EnemyShort::EnemyShort() {// 最初の位置
	enemyStartPos = {-10.0f, 1.0f, 5.0f};

	// プレイヤーとの距離を測る変数
	distanceToPlayer_ = 5.0f;
}

EnemyShort::~EnemyShort() {}

void EnemyShort::Move() {
	ApproachPlayer();
	worldTransform_.translation_ += move_;
}

void EnemyShort::Attack() {}
