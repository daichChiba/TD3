#include "EnemyBoss.h"

#include "../player/PlayerActor.h"

using namespace MathUtility;

void EnemyBoss::Move() { 	
	time += 1.0f;

	MoveToPlayer();
}

void EnemyBoss::MoveToPlayer() {
	// プレイヤーの位置を取得
	Vector3 playerPosition = PlayerWorldTransform_->translation_;

	// 自分の現在位置
	Vector3 currentPosition = worldTransform_.translation_;

	// 移動速度
	const float speed = 0.8f;

	// ジグザグの振幅と周波数
	const float amplitude = 50.0f; // ジグザグの幅
	const float frequency = 2.0f;  // ジグザグの速さ

	// 時間を基にジグザグのオフセットを計算
	float zigzagOffset = amplitude * std::sin(frequency * time);

	// プレイヤーへの方向ベクトルを計算
	Vector3 direction = playerPosition - currentPosition;
	direction = Normalize(direction);

	// ジグザグの横方向のベクトルを計算
	Vector3 perpendicular(-direction.y, direction.x); // 直交ベクトル

	// ジグザグのオフセットを加えた移動ベクトル
	Vector2 moveVector = direction * speed + perpendicular * zigzagOffset;

	// 新しい位置を計算
	Vector2 newPosition = currentPosition + moveVector;

	// 新しい位置を設定
	this->SetPosition(newPosition);
}
