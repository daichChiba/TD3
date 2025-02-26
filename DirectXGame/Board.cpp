#include "Board.h"
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <array>

// コンストラクタ: ボードの初期化
Board::Board() {
	// タイルの数を設定し、初期値を割り当てる
	tiles.resize(SIZE * SIZE);
	for (int i = 0; i < SIZE * SIZE - 1; ++i) {
		tiles[i] = i + 1;
	}
	// 空白のタイルを最後の要素に設定
	tiles[SIZE * SIZE - 1] = EMPTY_TILE;
	// 空白のタイルのインデックスを設定
	emptyIndex = SIZE * SIZE - 1;
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
}

// タイルを移動する関数
bool Board::MoveTile(int index) {
	// 選択されたタイルの行と列を計算
	row = index / SIZE;
	col = index % SIZE;
	// 空白のタイルの行と列を計算
	emptyRow = emptyIndex / SIZE;
	emptyCol = emptyIndex % SIZE;

	// 選択されたタイルが空白のタイルと隣接しているかチェック
	if ((std::abs(row - emptyRow) + std::abs(col - emptyCol)) == 1) {
		// タイルを交換
		std::swap(tiles[index], tiles[emptyIndex]);
		// 空白のタイルのインデックスを更新
		emptyIndex = index;
		return true;
	}

	return false;
}

// ImGui を使用してスライドパズルを表示する関数
void Board::ImGuiX() {
	ImGui::Begin("Slide Puzzle");

	// ボードのタイルを表示
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			int index = y * SIZE + x;
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
			if (x < SIZE - 1)
				ImGui::SameLine();
		}
	}

	// シャッフルボタン
	if (ImGui::Button("Shuffle")) {
		Shuffle();
	}

	ImGui::End();
}

// スライドパズルを表示する関数
void Board::ShowSliderPuzzle() { ImGuiX(); }