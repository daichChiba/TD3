#include "EnemyActor.h"
using namespace MathUtility;


void EnemyActor::Initialize(Model* model, Model* bulletModel, const Vector3 pos, ActorManager* actorManager) {
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif

	model_ = model;
	BulletModel_ = bulletModel;


	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	actorManager_ = actorManager;

	move_ = Vector3{0.0f, 0.0f, 0.1f};

}

void EnemyActor::Update() {
	Move();
	Attack();

	/*move_ = Normalize(move_) * kSpeed_;

	if (camera_) {

		Matrix4x4 matRotX = MakeRotateXMatrix(camera_->rotation_.x);
		Matrix4x4 matRotY = MakeRotateYMatrix(camera_->rotation_.y);
		Matrix4x4 matRotZ = MakeRotateZMatrix(camera_->rotation_.z);

		Matrix4x4 matRot = matRotX * matRotY * matRotZ;

		move_ = TransformNormal(move_, matRot);*/

		
	/*}*/

	worldTransform_.translation_ -= move_;
	DrawImGui();

	worldTransform_.UpdateMatrix();
	


}

void EnemyActor::Draw(Camera& camera) {
	 model_->Draw(worldTransform_, camera); }

void EnemyActor::DrawImGui() {
	ImGui::Begin("enemy");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x);
	ImGui::Text("move : %.3f,%.3f,%.3f", move_.x, move_.y, move_.z);
	ImGui::End();
}

//void EnemyActor::Move() {
//
//}
//
//void EnemyActor::Attack() {
//
//}
