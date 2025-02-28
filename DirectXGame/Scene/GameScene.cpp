#include "GameScene.h"
#include <iostream>

GameScene::GameScene() : board(nullptr){}

GameScene::~GameScene() { delete board; }

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	board = new Board();
	
}

void GameScene::Update() {
	
	board->ImGuiX();

	//タイルを配置する
	PlaceTiles();
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

	 board->ShowSliderPuzzle();

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

void GameScene::PlaceTiles() {
	// ImGuiを使用してタイルを配置する
	ImGui::Begin("Place Tiles");

	for (int i = 0; i < board->row * board->col; i++) {
		int value = board->tiles[i];
		if (ImGui::InputInt(("Tile" + std::to_string(i)).c_str(), &value)) {
			board->PlaceTile(i, value);
		}
	}
	ImGui::End();
}
