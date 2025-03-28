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

void EnemyShort::ApproachPlayer() {
	if (PlayerWorldTransform_ == nullptr) {
		return;
	}

	// プレイヤーの位置を取得
	Vector3 playerPos = PlayerWorldTransform_->translation_;

	// 敵の位置を取得
	Vector3 enemyPos = worldTransform_.translation_;

	// プレイヤーに向かうベクトルを計算
	Vector3 direction = playerPos - enemyPos;
	float distance = Length(direction);

	// モデルの向きをプレイヤーの方向に合わせる
	float angle = atan2(-direction.x, -direction.z);
	worldTransform_.rotation_.y = angle;

	  // プレイヤーに近づく処理
	if (distance > distanceToPlayer_) {
		direction = Normalize(direction);
		move_ = direction * kSpeed_;

		
	} else {
		move_ = Vector3{0.0f, 0.0f, 0.0f};
	}
}
