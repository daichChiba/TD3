#include "ClearScene.h"

void ClearScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	clearTexture_ = TextureManager::Load("Scene/gameClear.png");
	clearSprite_ = Sprite::Create(clearTexture_, {0, 0});
	pushTexture_ = TextureManager::Load("PushReturn.png");
	pushSprite_ = Sprite::Create(pushTexture_, {320, 600});

	// サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("BGM/ClearBGM.mp3");
	// 音声再生
	audio_->PauseWave(soundDataHandle_);
	// 第2引数でループ再生を指定
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
}

void ClearScene::Update() {
	if (Input::GetInstance()->ReleseKey(DIK_RETURN)) {
		// 音声停止
		audio_->StopWave(voiceHandle_);
		finished_ = true;
	}
	DrawImGui();
}
void ClearScene::Draw() {
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

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	clearSprite_->Draw();
	pushSprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void ClearScene::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("ClearScene");
	ImGui::Text("ClearScene");
	ImGui::End();
#endif
}
