#include "GameScene.h"
#include <iostream>

GameScene::GameScene() : puzzle15_(nullptr) {}

GameScene::~GameScene() { delete puzzle15_; }

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ボードの数を設定し、初期値を割り当てる
	puzzle15_ = new Puzzle15(3, 3);
	
}

void GameScene::Update() {

	puzzle15_->ImGuiX();

	//タイルを配置する
	PlaceTiles();


	puzzle15_->Update();

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

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

	 //board->ShowSliderPuzzle();

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	puzzle15_->Draw();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::PlaceTiles() {
	// ImGuiを使用してタイルを配置する
	ImGui::Begin("Place Tiles");

	/*for (int i = 0; i < puzzle15_->row * puzzle15_->col; i++) {
		int value = puzzle15_->tiles[i];
		if (ImGui::InputInt(("Tile" + std::to_string(i)).c_str(), &value)) {
			puzzle15_->PlaceTile(i, value);
		}
	}*/
	ImGui::End();
}
