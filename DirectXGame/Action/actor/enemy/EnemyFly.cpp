#include "EnemyFly.h"
using namespace MathUtility;


EnemyFly::EnemyFly(){
	// 最初の位置
	enemyStartPos = {1.0f, 5.0f, 1.0f};
	// プレイヤーとの高さを測る変数
	minDistanceY_ = 5.0f;
	// プレイヤーとの距離を測る変数
	distanceToPlayer_ = 3.0f;
}

EnemyFly::~EnemyFly() {}


void EnemyFly::Move() {
	ApproachPlayer();
}

void EnemyFly::Attack() {
	// 攻撃のコード
}

void EnemyFly::ApproachPlayer() {

  if (PlayerWorldTransform_ == nullptr) {
		return;
	}

	// プレイヤーの位置を取得
	Vector3 playerPos = PlayerWorldTransform_->translation_;

	// 敵の位置を取得
	Vector3 enemyPos = worldTransform_.translation_;

	// プレイヤーに向かうベクトルを計算（Y軸方向の移動を無視）
	Vector3 direction = playerPos - enemyPos;
	direction.y = 0.0f; // Y軸方向の移動を無視
	float distance = Length(direction);

	// プレイヤーの真上に到達したら動きを止める
	if (fabs(playerPos.y - enemyPos.y) < minDistanceY_ && distance < distanceToPlayer_) {
		move_ = Vector3{0.0f, 0.0f, 0.0f};
		return;
	}

	// プレイヤーが一定距離以上離れたら再び動き出す
	if (distance >= distanceToPlayer_) {
		direction = Normalize(direction);
		move_ = direction * kSpeed_;
	} else {
		move_ = Vector3{0.0f, 0.0f, 0.0f};
	}
}
