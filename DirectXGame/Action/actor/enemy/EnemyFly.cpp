#include "EnemyFly.h"

EnemyFly::EnemyFly() : random_(std::random_device{}()), randomDist_(-1.0f, 1.0f) {}

EnemyFly::~EnemyFly() {}

void EnemyFly::Initialize() {
	// 初期化コード
}

void EnemyFly::Move() {
	//タイマーを更新
	moveTimer_ += kSpeed_;

	//一定間隔でランダムな値を生成して移動ベクトルに適応
	if (moveTimer_ >= kMoveInterval_) {

	   // ランダムな値を生成して移動ベクトルに適用
	   move_.x = randomDist_(random_) * kSpeed_;
	   move_.y = randomDist_(random_) * kSpeed_;
	   move_.z = randomDist_(random_) * kSpeed_;

	   //タイマーをリセット
	   moveTimer_ = 0.0f;
	}


	// 移動をワールド変換に反映
	worldTransform_.translation_.x += move_.x;
	worldTransform_.translation_.y += move_.y;
	worldTransform_.translation_.z += move_.z;

	// 移動ベクトルをリセット
	move_ = {0.0f, 0.0f, 0.0f};

}

void EnemyFly::Attack() {
	// 攻撃のコード
}