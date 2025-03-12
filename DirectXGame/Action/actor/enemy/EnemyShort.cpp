#include "EnemyShort.h"
#include "../ActorManager.h"

void EnemyShort::Initialize() {}

void EnemyShort::Move() {
	 move_.x += kSpeed_;

	 worldTransform_.translation_.x += move_.x;

	 move_.x = 0.0f;
}

void EnemyShort::Attack() {}
