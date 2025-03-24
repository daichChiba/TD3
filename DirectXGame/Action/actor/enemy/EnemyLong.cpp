#include "EnemyLong.h"
using namespace MathUtility;


EnemyLong::EnemyLong() {
	// 最初の位置
	enemyStartPos = {1.0f, 1.0f, 1.0f};
	// プレイヤーとの高さを測る変数
	minDistanceY_ = 5.0f;
	// プレイヤーとの距離を測る変数
	distanceToPlayer_ = 3.0f;
}

EnemyLong::~EnemyLong() {}

void EnemyLong::Move() {
	move_.x += kSpeed_;

	worldTransform_.translation_.x += move_.x;

	move_.x = 0.0f;
}

void EnemyLong::Attack() {}

void EnemyLong::ApproachPlayer() {

 //if (PlayerWorldTransform_ == nullptr) {
	//	return;
	//}

	//// プレイヤーの位置を取得
	//Vector3 playerPos = PlayerWorldTransform_->translation_;

	//// 敵の位置を取得
	//Vector3 enemyPos = worldTransform_.translation_;

	//// プレイヤーに向かうベクトルを計算
	//Vector3 direction = playerPos - enemyPos;
	//float distance = Length(direction);

	//// プレイヤーの真上に到達したら動きを止める
	//if (fabs(playerPos.y - enemyPos.y) < minDistanceY_ && distance < distanceToPlayer_) {
	//	move_ = Vector3{0.0f, 0.0f, 0.0f};
	//	return;
	//}

	//// プレイヤーが一定距離以上離れたら再び動き出す
	//if (distance >= distanceToPlayer_) {
	//	direction = Normalize(direction);
	//	move_ = direction * kSpeed_;
	//} else {
	//	move_ = Vector3{0.0f, 0.0f, 0.0f};
	//}
}

