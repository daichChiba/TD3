#include "EnemyActor.h"

#include "../ActorManager.h"
#include "../player/PlayerActor.h"

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

	DrawImGui();

	worldTransform_.UpdateMatrix();
}

void EnemyActor::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }

void EnemyActor::DrawImGui() {
	#ifdef  _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
	ImGui::Text("move : %.3f,%.3f,%.3f", move_.x, move_.y, move_.z);
	ImGui::Text("pPos : %.3f,%.3f,%.3f", PlayerWorldTransform_->translation_.x,  PlayerWorldTransform_->translation_.y,  PlayerWorldTransform_->translation_.z);
	ImGui::End();
#endif
}

void EnemyActor::OnCollision()
{
	isDelete_ = true;
}

void EnemyActor::ApproachPlayer()
{
	if (PlayerWorldTransform_ == nullptr) {
        return;
    }

    // プレイヤーの位置を取得
    Vector3 playerPos = PlayerWorldTransform_->translation_;

    // 敵の位置を取得
    Vector3 enemyPos = worldTransform_.translation_;

    // プレイヤーに向かうベクトルを計算
    Vector3 direction = playerPos - enemyPos;
    float distance = Length(direction);

    direction = Normalize(direction);
	
	if(distance > 3.0f)
	{
		move_ = direction * kSpeed_;
		return;
	}
	return;
    
}
