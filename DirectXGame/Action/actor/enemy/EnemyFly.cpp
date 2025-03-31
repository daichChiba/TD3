#include "EnemyFly.h"

#include "../ActorManager.h"
#include "../player/PlayerActor.h"

#include "../bullet/BulletActor.h"
#include "../bullet/BulletFlyEnemy.h"

using namespace MathUtility;

EnemyFly::EnemyFly() {
	enemyStartPos = {1.0f, 5.0f, 1.0f};
	kMinDistanceY_ = 5.0f;
}

EnemyFly::~EnemyFly() {}


void EnemyFly::Move() { 
	ApproachPlayer();
	ImGui::Begin("enemyFly");
	ImGui::Text("enemyFly");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
	ImGui::DragFloat3("move", &move_.x);
	ImGui::DragFloat("attackTimer", &attackTiemr);
	ImGui::End();
}

void EnemyFly::Attack() {
	// 攻撃のコード

	attackTiemr -= kFlameTime;

	if ((std::fabs(move_.x) <= 0.0f && fabs(move_.z) <= 0.0f) && attackTiemr < 0.0f) {
		std::shared_ptr<BulletActor> attack = std::make_shared<BulletFlyEnemy>();
		attack->Initialize(BulletModel_, worldTransform_.translation_);

		Vector3 currentPos = worldTransform_.translation_;
		Vector3 targetPos = actorManager_->GetPlayer()->GetWorldTransfrom()->translation_;

		// プレイヤー方向へのベクトルを計算
		Vector3 direction = targetPos - currentPos;
		direction = Normalize(direction);

		// 弾の移動ベクトルを設定
		attack->SetMove(direction * 0.1f);
		attack->SetEnumClassEnemy();

		actorManager_->AddBullet(attack); // プレイヤーが持っているゲームシーンからゲームシーンにポインタを渡す
	
		attackTiemr = kAttackTiem;
	}
}