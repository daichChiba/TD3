#include "GameScene.h"

#include "../Action/FolloCamera.h"
#include "../Action/actor/ActorManager.h"
#include "../Action/actor/player/PlayerActor.h"

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

	actorManager = new ActorManager();
	actorManager->SetGeamScene(this);
	actorManager->Initialize(PlayerModel_, playerBulletModel_, cubeModel_, cubeModel_);
	
}

void GameScene::Update() {
	actorManager->Update();

	skyDomeTrans.UpdateMatrix();
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
