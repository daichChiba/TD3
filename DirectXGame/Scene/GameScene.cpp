#include "GameScene.h"

#include "../Action/FolloCamera.h"
#include "../Action/actor/ActorManager.h"
#include "../Action/actor/player/PlayerActor.h"
#include "../Action/actor/enemy/EnemyActor.h"
#include "../Action/actor/enemy/EnemyTest.h"


GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	cubeModel_ = Model::CreateFromOBJ("cube");
	skyDome_ = Model::CreateFromOBJ("SkyDome", true);
	ground_ = Model::CreateFromOBJ("ground");

	skyDomeTrans.Initialize();

	PlayerModel_ = Model::CreateFromOBJ("Player");
	playerBulletModel_ = Model::CreateFromOBJ("cube");

	//////////////////////////////
	//Enemy
	
	//enemyModel_ = Model::CreateFromOBJ("Player");
	/*enemy_ = new EnemyManager();
	enemy_->Initialize(PlayerModel_, PlayerModel_, Vector3(0.0f, 0.0f, 0.0f), actorManager_);
	*/
	
	// // 各敵の動きを異なる方向に設定
	//Enemy[0]->SetMove(Vector3{0.1f, 0.0f, 0.0f});  // 右方向
	//Enemy[1]->SetMove(Vector3{-0.1f, 0.0f, 0.0f}); // 左方向
	//Enemy[2]->SetMove(Vector3{0.0f, 0.0f, -0.1f}); // 後ろ方向

	//////////////////////////////

	actorManager = new ActorManager();
	actorManager->SetGeamScene(this);
	actorManager->Initialize(PlayerModel_, playerBulletModel_, cubeModel_, cubeModel_);
	
}

void GameScene::Update() {
	actorManager->Update();

	skyDomeTrans.UpdateMatrix();

	//////////////////////////////
	// Enemy
	/*Enemy_->Update();*/
	//enemy_->Update();
	//////////////////////////////

}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	skyDome_->Draw(skyDomeTrans, *actorManager->SetCamera());
	ground_->Draw(skyDomeTrans, *actorManager->SetCamera());

	actorManager->Draw();
	//enemy_->Draw( *actorManager->SetCamera());
	//////////////////////////////
	// Enemy
	//Enemy_->Draw(*actorManager->SetCamera());

	//////////////////////////////



	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
