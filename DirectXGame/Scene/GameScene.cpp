#include "GameScene.h"
#include <iostream>

GameScene::GameScene(){}

GameScene::~GameScene() { 
	delete puzzle15_;
	
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ボードの数を設定し、初期値を割り当てる
	//puzzle15_ = new Puzzle15(3, 3);
	puzzle15_ = new Puzzle15;
	puzzle15_->LoadPuzzle15Csv("Resources/panels.csv");

	GeneratePanels();

	for (uint32_t i = 0; i < 3; ++i) {
		for (uint32_t j = 0; j < 3; ++j) {
			slidePuzzle15_[i][j] = TextureManager::Load("puzzle15_Tile");
			puzzle_[i][j] = Sprite::Create(slidePuzzle15_[i][j], {0, 0});
		}
	}

	
	
	//// 2D背景
	//puzzle_ = TextureManager::Load("badEndSkydome/badEndSkydome.png");
	//slidePuzzle15_ = Sprite::Create(puzzle_, {0, 0});

}

void GameScene::Update() {

	//puzzle15_->ImGuiX();

	//タイルを配置する
//	PlaceTiles();


	//puzzle15_->Update();

}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	//slidePuzzle15_->Draw();

	/*for (std::vector<WorldTransform*>& worldTransformBlocksLine : worldTransformPanels_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlocksLine) {
			if (!worldTransformBlock)*/
			//	continue;
			puzzle_->Draw();
	/*	}
	}*/

		/*	for (std::vector<WorldTransform*>& worldTransformPanelsLine : worldTransformPanels_) {
		        for (WorldTransform* worldTransformPanel : worldTransformPanelsLine) {
			        if (!worldTransformPanel)
				        continue;
			        puzzle_->Draw(worldTransformPanel);
		        }
	        }*/

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

	//slidePuzzle15_->Draw();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GeneratePanels() {
	uint32_t numPanelVirtical = puzzle15_->GetNumPanelVirtical();
	uint32_t numPanelHorizontal = puzzle15_->GetNumPanelHorizontal();

	// 要素数を変更する
	// 列数を設定（縦方向のブロック数）
	worldTransformPanels_.resize(numPanelVirtical);
	for (uint32_t i = 0; i < numPanelVirtical; i++) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformPanels_[i].resize(numPanelHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numPanelVirtical; ++i) {
		for (uint32_t j = 0; j < numPanelHorizontal; ++j) {
			if (puzzle15_->GetPuzzle15TypeByIndex(j, i) == Puzzle15Panel::kOne &&
				puzzle15_->GetPuzzle15TypeByIndex(j, i) == Puzzle15Panel::kTwo &&
			    puzzle15_->GetPuzzle15TypeByIndex(j, i) == Puzzle15Panel::kThree &&
				puzzle15_->GetPuzzle15TypeByIndex(j, i) == Puzzle15Panel::kFour&&
				puzzle15_->GetPuzzle15TypeByIndex(j, i) == Puzzle15Panel::kFive&&
			    puzzle15_->GetPuzzle15TypeByIndex(j, i) == Puzzle15Panel::kSix && 
				puzzle15_->GetPuzzle15TypeByIndex(j, i) == Puzzle15Panel::kSeven&&
			    puzzle15_->GetPuzzle15TypeByIndex(j, i) == Puzzle15Panel::kEight) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformPanels_[i][j] = worldTransform;
				worldTransformPanels_[i][j]->translation_ = puzzle15_->GetPuzzle15PositionByIndex(j, i);
			}
		}
	}
}

//void GameScene::PlaceTiles() {
//	// ImGuiを使用してタイルを配置する
//	ImGui::Begin("Place Tiles");
//
//	/*for (int i = 0; i < puzzle15_->row * puzzle15_->col; i++) {
//		int value = puzzle15_->tiles[i];
//		if (ImGui::InputInt(("Tile" + std::to_string(i)).c_str(), &value)) {
//			puzzle15_->PlaceTile(i, value);
//		}
//	}*/
//	ImGui::End();
//}
