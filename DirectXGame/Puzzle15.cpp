#include "Puzzle15.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <queue>
#include <unordered_set>

// カスタムハッシュ関数を定義
struct VectorHash {
	std::size_t operator()(const std::vector<int>& v) const {
		std::size_t seed = v.size();
		for (auto& i : v) {
			seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

// コンストラクタ: ボードの初期化
Puzzle15::Puzzle15(int row, int col) : row(row), col(col), moveCount(0) {
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
void Puzzle15::Shuffle() {
	// 乱数生成器の初期化
	std::random_device rd;
	std::mt19937 g(rd());

	// タイルをランダムにシャッフル
	std::shuffle(tiles.begin(), tiles.end(), g);
	// シャッフル後の空白のタイルのインデックスを更新
	emptyIndex = (int)std::distance(tiles.begin(), std::find(tiles.begin(), tiles.end(), EMPTY_TILE));
	//移動回数をリセット
	ResetMoveCount();

	//移動履歴をクリア
	while (!moveHistory.empty()) {
		moveHistory.pop();
	}
}

// タイルを移動する関数
bool Puzzle15::MoveTile(int index) {
	// 選択されたタイルの行と列を計算
	rows = index / col;
	cols = index % col;
	// 空白のタイルの行と列を計算
	emptyRow = emptyIndex / col;
	emptyCol = emptyIndex % col;

	 // タイルが同じ行または同じ列にある場合に移動を許可
	if (rows == emptyRow) {
		// 同じ行にある場合
		if (cols < emptyCol) {
			// 左側にある場合
			for (int i = emptyCol; i > cols; --i) {
				std::swap(tiles[emptyRow * col + i], tiles[emptyRow * col + i - 1]);
			}
		} else if (cols > emptyCol) {
			// 右側にある場合
			for (int i = emptyCol; i < cols; ++i) {
				std::swap(tiles[emptyRow * col + i], tiles[emptyRow * col + i + 1]);
			}
		}
		moveHistory.push({emptyIndex, index});
		emptyIndex = index;
		moveCount++;
		return true;
	} else if (cols == emptyCol) {
		// 同じ列にある場合
		if (rows < emptyRow) {
			// 上側にある場合
			for (int i = emptyRow; i > rows; --i) {
				std::swap(tiles[i * col + emptyCol], tiles[(i - 1) * col + emptyCol]);
			}
		} else if (rows > emptyRow) {
			// 下側にある場合
			for (int i = emptyRow; i < rows; ++i) {
				std::swap(tiles[i * col + emptyCol], tiles[(i + 1) * col + emptyCol]);
			}
		}
		moveHistory.push({emptyIndex, index});
		emptyIndex = index;
		moveCount++;
		return true;
	}

	return false;
}

// 最後の移動を元に戻す関数
void Puzzle15::UndoMove() {
	if (!moveHistory.empty()) {
		auto [prevEmptyIndex, prevTileIndex] = moveHistory.top();
		moveHistory.pop();
		std::swap(tiles[emptyIndex], tiles[prevTileIndex]);
		emptyIndex = prevEmptyIndex;
		moveCount--;
	}
}

// ヒューリスティック関数
// 問題の正確な解決策がない場合や解決策を取得する時間が長すぎる場合に、問題を解決するためのショートカットとして使用される関数
int Puzzle15::Heuristic(const std::vector<int>& state) {
	int h = 0;
	for (int i = 0; i < state.size(); ++i) {
		if (state[i] != EMPTY_TILE) {
			int targetRow = (state[i] - 1) / col;
			int targetCol = (state[i] - 1) % col;
			int currentRow = i / col;
			int currentCol = i % col;
			h += std::abs(targetRow - currentRow) + std::abs(targetCol - currentCol);
		}
	}
	return h;
}

//最短手数を計算する関数
 int Puzzle15::CalculateMinimumMoves() {
	std::priority_queue<std::pair<int, std::vector<int>>, std::vector<std::pair<int, std::vector<int>>>, std::greater<>> pq;
	std::unordered_set<std::vector<int>, VectorHash> visited;
	pq.push({Heuristic(tiles), tiles});
	visited.insert(tiles);

	while (!pq.empty()) {
		auto [cost, state] = pq.top();
		pq.pop();

		if (std::is_sorted(state.begin(), state.end() - 1) && state.back() == EMPTY_TILE) {
			return cost;
		}

		emptyIndex = (int)std::distance(state.begin(), std::find(state.begin(), state.end(), EMPTY_TILE));
		emptyRow = emptyIndex / col;
		emptyCol = emptyIndex % col;

		std::vector<std::pair<int, int>> directions = {
		    {-1, 0 },
             {1,  0 },
             {0,  -1},
             {0,  1 }
         };
		for (auto [dr, dc] : directions) {
			int newRow = emptyRow + dr;
			int newCol = emptyCol + dc;
			if (newRow >= 0 && newRow < row && newCol >= 0 && newCol < col) {
				std::vector<int> newState = state;
				std::swap(newState[emptyRow * col + emptyCol], newState[newRow * col + newCol]);
				if (visited.find(newState) == visited.end()) {
					pq.push({cost + 1 + Heuristic(newState), std::move(newState)});
					visited.insert(newState);
				}
			}
		}
	}

	return -1; // 解が見つからない場合
 }

// ImGui を使用してスライドパズルを表示する関数
void Puzzle15::ImGuiX() {
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
		Reset();
	}

	//元に戻すボタン
	if (ImGui::Button("Undo")) {
		UndoMove();
	}

	// 移動回数を表示
	ImGui::Text("Move Count: %d", moveCount);

	//最短手数を表示
	minMoves = CalculateMinimumMoves();
	if (minMoves != -1) {
		ImGui::Text("Minimum Move : %d", minMoves);
	} else {
		ImGui::Text("No solution found");
	}

	ImGui::End();
}

//パズルが解けたかどうかを確認する関数
bool Puzzle15::IsSolved() {
	for (int i = 0; i < row * col - 1; ++i) {
		if (tiles[i] != i + 1) {
			return false;
		}
	}
	return tiles[row * col - 1] == EMPTY_TILE;
}

//タイルを任意の場所に配置する関数
void Puzzle15::PlaceTile(int index, int value) {
	tiles[index] = value;
	if (value == EMPTY_TILE) {
		emptyIndex = index;
	}
}

//パズルを初期化状態にリセットする関数
void Puzzle15::Reset() {
	tiles = initialTiles;
	emptyIndex = initialEmptyIndex;
	//移動回数をリセット
	ResetMoveCount();
	//移動履歴をクリア
	while (!moveHistory.empty()) {
		moveHistory.pop();
	}
}

//移動回数をリセットする関数
void Puzzle15::ResetMoveCount() { moveCount = 0; }




// スライドパズルを表示する関数
void Puzzle15::ShowSliderPuzzle() { ImGuiX(); }

