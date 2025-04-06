#include "PuzzleScene.h"

void PuzzleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// パズルマネージャーの初期化
	puzzleManager_ = new PuzzleManager();
	puzzleManager_->Initialize();
	// 終了フラグの初期化
	finished_ = false;
}

void PuzzleScene::Update() {
	// パズルマネージャーの更新
	puzzleManager_->Update();
	if (puzzleManager_->GetIsClear()) {
		finished_ = true;
	}
	DrawImGui();
}

void PuzzleScene::Draw() {
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

	puzzleManager_->SpriteDraw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void PuzzleScene::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("PuzzleScene");
	ImGui::Text("PuzzleScene");
	ImGui::End();
#endif
}
