#include "EnemyFly.h"

EnemyFly::EnemyFly() : random_(std::random_device{}()), randomDist_(-1.0f, 1.0f) {}

EnemyFly::~EnemyFly() {}

void EnemyFly::Initialize() {
	// 初期化コード
}

void EnemyFly::Move() {
	//// 動きのコード
	//move_.z += kSpeed_;
	//move_.y += 10.0f;

	//worldTransform_.translation_.z += move_.z;
	//worldTransform_.rotation_.z += move_.z;
	//worldTransform_.translation_.y = move_.y;

	//move_.z = 0.0f;
	//move_.y = 0.0f;

	  // ランダムな値を生成して移動ベクトルに適用
	move_.x = randomDist_(random_) * kSpeed_;
	move_.y = randomDist_(random_) * kSpeed_;
	move_.z = randomDist_(random_) * kSpeed_;

	// 移動をワールド変換に反映
	worldTransform_.translation_.y += move_.y;

	// 移動ベクトルをリセット
	move_ = {0.0f, 0.0f, 0.0f};

}

void EnemyFly::Attack() {
	// 攻撃のコード
}