#include "EnemyFly.h"
#include "../bullet/BulletActor.h"

EnemyFly::EnemyFly(){
	enemyStartPos = {1.0f, 5.0f, 1.0f};
	minDistanceY_ = 5.0f;
}

EnemyFly::~EnemyFly() {}

//void EnemyFly::Update() {
//	FlyImGui();
//}
//
//void EnemyFly::FlyImGui() {
//	ImGui::Begin("enemy");
//	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
//	ImGui::Text("move : %.3f,%.3f,%.3f", move_.x, move_.y, move_.z);
//	ImGui::Text("pPos : %.3f,%.3f,%.3f", PlayerWorldTransform_->translation_.x, PlayerWorldTransform_->translation_.y, PlayerWorldTransform_->translation_.z);
//	ImGui::End();
//}

void EnemyFly::Move() {
	ApproachPlayer();
}

void EnemyFly::Attack() {
	// 攻撃のコード

	if (move_.x < 0.0f && move_.z < 0.0f)
	{
		std::shared_ptr<BulletActor> attack = std::make_shared<BulletPlayerNormalAttack>();
		attack->Initialize(BulletModel_, worldTransform_.translation_);
		
	}
}