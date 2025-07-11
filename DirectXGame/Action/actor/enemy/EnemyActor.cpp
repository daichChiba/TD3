#include "EnemyActor.h"

#include "../ActorManager.h"
#include "../player/PlayerActor.h"

#include <Windows.h>

using namespace MathUtility;

void EnemyActor::Initialize(Model* model, Model* bulletModel, const Vector3 pos, ActorManager* actorManager) {
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif

	model_ = model;
	BulletModel_ = bulletModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos + enemyStartPos;

	actorManager_ = actorManager;

	move_ = Vector3{0.0f, 0.0f, 0.0f};

	PlayerWorldTransform_ = actorManager_->GetPlayer()->GetWorldTransfrom();
}

void EnemyActor::Update() {
	Move();
	Attack();

	worldTransform_.translation_ += move_;

	// モデルの向きをプレイヤーの方向に合わせる
	float angle = atan2(-direction.x, -direction.z);
	worldTransform_.rotation_.y = angle;


	DrawImGui();

	worldTransform_.UpdateMatrix();
}

void EnemyActor::Draw(Camera& camera) {
	model_->Draw(worldTransform_, camera);
}

void EnemyActor::DrawImGui() {
	#ifdef  _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
	ImGui::Text("move : %.3f,%.3f,%.3f", move_.x, move_.y, move_.z);
	//ImGui::Text("pPos : %.3f,%.3f,%.3f", PlayerWorldTransform_->translation_.x,  PlayerWorldTransform_->translation_.y,  PlayerWorldTransform_->translation_.z);
	ImGui::End();
#endif
}

void EnemyActor::OnCollision(int damage)
{
	hp -= damage;
	if(hp <= 0)
	isDelete_ = true;
}

void EnemyActor::ApproachPlayer() {
    if (PlayerWorldTransform_ == nullptr) {
        return;
    }

    // プレイヤーの位置を取得
    Vector3 playerPos = PlayerWorldTransform_->translation_;

    // 敵の位置を取得
    Vector3 enemyPos = worldTransform_.translation_;

	// プレイヤーに向かうベクトルを計算（Y軸方向の移動を無視）
	direction = playerPos - enemyPos;
	float distance = Length(direction);

    // プレイヤーの真上に到達したら動きを止める
    if (fabs(playerPos.y - enemyPos.y) < kMinDistanceY_ && distance < kMinDistanceX_) {
        move_ = Vector3{0.0f, 0.0f, 0.0f};
        return;
    }

	 // プレイヤーが一定距離以上離れたら再び動き出す
	if (distance >= 3.0f) {
		direction = Normalize(direction);
		move_ = direction * kSpeed_;
	} else {
		move_ = Vector3{0.0f, 0.0f, 0.0f};
	}

    direction = Normalize(direction);

    if (distance > kApproachDistance_) {
        move_ = direction * kSpeed_;
        return;
    }
    return;
}