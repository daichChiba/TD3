#include "Board.h"
#include <random>
#include <algorithm>
#include <chrono>

// コンストラクタ: ボードの初期化
Board::Board(int row, int col) : row(row), col(col), moveCount(0){
	// タイルの数を設定し、初期値を割り当てる
	tiles.resize(row * col);
	initialTiles.resize(row * col);
	for (int i = 0; i < row * col - 1; ++i) {
		tiles[i] = i + 1;
		initialTiles[i] = i + 1;
	}

	// 空白のタイルを最後の要素に設定
	tiles[row * col - 1] = EMPTY_TILE;
	initialTiles[row * col - 1] = EMPTY_TILE;

	// 空白のタイルのインデックスを設定
	emptyIndex = row * col - 1;
	initialEmptyIndex = row * col - 1;

	// タイルをシャッフル
	Shuffle();
}

// タイルをシャッフルする関数
void Board::Shuffle() {
	// 乱数生成器の初期化
	std::random_device rd;
	std::mt19937 g(rd());
	// タイルをランダムにシャッフル
	std::shuffle(tiles.begin(), tiles.end(), g);
	// シャッフル後の空白のタイルのインデックスを更新
	emptyIndex = (int)std::distance(tiles.begin(), std::find(tiles.begin(), tiles.end(), EMPTY_TILE));
	//移動回数をリセット
	ResetMoveCount();
}

// タイルを移動する関数
bool Board::MoveTile(int index) {
	// 選択されたタイルの行と列を計算
	rows = index / col;
	cols = index % col;
	// 空白のタイルの行と列を計算
	emptyRow = emptyIndex / col;
	emptyCol = emptyIndex % col;

	// 選択されたタイルが空白のタイルと隣接しているかチェック
	if ((std::abs(rows - emptyRow) + std::abs(cols - emptyCol)) == 1) {
		// タイルを交換
		std::swap(tiles[index], tiles[emptyIndex]);

		// 空白のタイルのインデックスを更新
		emptyIndex = index;

		//移動回数をインクリメント
		moveCount++;
		return true;
	}
	return false;
}

// ImGui を使用してスライドパズルを表示する関数
void Board::ImGuiX() {
	ImGui::Begin("Slide Puzzle");

	// ボードのタイルを表示
	for (int y = 0; y < row; y++) {
		for (int x = 0; x < col; x++) {
			int index = y * col + x;
			// タイルが空白でない場合、ボタンとして表示
			if (tiles[index] != EMPTY_TILE) {
				if (ImGui::Button(std::to_string(tiles[index]).c_str(), ImVec2(50, 50))) {
					// ボタンがクリックされたらタイルを移動
					MoveTile(index);
				}
			} else {
				// 空白のタイルは空白のボタンとして表示
				ImGui::Button(" ", ImVec2(50, 50));
			}

			// 右端のタイル以外は横に並べる
			if (x < col - 1)
				ImGui::SameLine();
		}
	}

	// シャッフルボタン
	if (ImGui::Button("Shuffle")) {
		Shuffle();
	}

	 // リセットボタン
	if (ImGui::Button("Reset")) {
		//Reset();
	}

	// 移動回数を表示
	ImGui::Text("Move Count: %d", moveCount);

	ImGui::End();

}

//パズルが解けたかどうかを確認する関数
bool Board::IsSolved() {
	for (int i = 0; i < row * col - 1; ++i) {
		if (tiles[i] != i + 1) {
			return false;
		}
	}
	return tiles[row * col - 1] == EMPTY_TILE;
}

//タイルを任意の場所に配置する関数
void Board::PlaceTile(int index, int value) {
	tiles[index] = value;
	if (value == EMPTY_TILE) {
		emptyIndex = index;
	}
}

//パズルを初期化状態にリセットする関数
void Board::Reset() {
	tiles = initialTiles;
	emptyIndex = initialEmptyIndex;
	//移動回数をリセット
	ResetMoveCount();
}

//移動回数をリセットする関数
void Board::ResetMoveCount() { moveCount = 0; }

// スライドパズルを表示する関数
void Board::ShowSliderPuzzle() { ImGuiX(); }