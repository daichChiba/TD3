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

	// 自分の現在位
	Vector3 currentPosition = worldTransform_.translation_;



}

void EnemyBoss::ShootCircle()
{


}
