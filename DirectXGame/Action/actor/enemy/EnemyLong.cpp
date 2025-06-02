#include "EnemyLong.h"
using namespace MathUtility;


EnemyLong::EnemyLong() {
	// 最初の位置
	enemyStartPos = {1.0f, 1.0f, 15.0f};
	
	hp = enemy_hp_;

	// プレイヤーとの距離を測る変数
	distanceToPlayer_ = 2.0f;
}

EnemyLong::~EnemyLong() {}

void EnemyLong::Move() {
	ApproachPlayer();
	worldTransform_.translation_ += move_;
}

void EnemyLong::Attack() {}

void EnemyLong::ApproachPlayer() {

 if (PlayerWorldTransform_ == nullptr) {
		return;
	}

	// プレイヤーの位置を取得
	Vector3 playerPos = PlayerWorldTransform_->translation_;

	// 敵の位置を取得
	Vector3 enemyPos = worldTransform_.translation_;

	// プレイヤーに向かうベクトルを計算
	direction = playerPos - enemyPos;
	float distance = Length(direction);

	  // プレイヤーに近づく処理
	if (distance > distanceToPlayer_) {
		direction = Normalize(direction);
		move_ = direction * kSpeed_;

		
	} else {
		move_ = Vector3{0.0f, 0.0f, 0.0f};
	}
}

