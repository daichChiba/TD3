#include "GameScene.h"

#include "../Action/FolloCamera.h"
#include "../Action/actor/ActorManager.h"
#include "../Action/actor/player/PlayerActor.h"
#include "../Action/actor/enemy/EnemyActor.h"
#include "../Action/actor/enemy/EnemyTest.h"


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete actorManager;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	cubeModel_ = Model::CreateFromOBJ("cube");
	skyDome_ = Model::CreateFromOBJ("SkyDome", true);
	ground_ = Model::CreateFromOBJ("ground");

	skyDomeTrans.Initialize();

	PlayerModel_ = Model::CreateFromOBJ("Remu");
	playerBulletModel_ = Model::CreateFromOBJ("cube");

	longModel_ = Model::CreateFromOBJ("Alien");
	shortModel = Model::CreateFromOBJ("pork");
	flyModel = Model::CreateFromOBJ("Fairy");

	actorManager = new ActorManager();
	actorManager->SetGeamScene(this);
	actorManager->Initialize(PlayerModel_, playerBulletModel_, longModel_,shortModel,flyModel, cubeModel_);

	// サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("BGM/GamePlay.mp3");
	// 音声再生
	audio_->PauseWave(soundDataHandle_);
	// 第2引数でループ再生を指定
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

}

void GameScene::Update() {
	actorManager->Update();

	skyDomeTrans.UpdateMatrix();

	if (actorManager->GetEnemyDeadConnt() == actorManager->GetClearEnemyCount()) {
		// 音声停止
		audio_->StopWave(voiceHandle_);
		DeadFinished_ = true;
	}

	if (actorManager->GetPlayer()->hp == 0) {
		// 音声停止
		audio_->StopWave(voiceHandle_);
		DeadFinished_ = true;
	}

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
