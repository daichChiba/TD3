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

void Puzzle15::Initialize() {
	
}

void Puzzle15::Update() {
	HandleInput();
	if (input_ && input_->TriggerKey(DIK_Z)) {
		UndoMove();
	}
}

void Puzzle15::Draw() {
	for (int y = 0; y < rows_; y++) {
		for (int x = 0; x < cols_; x++) {
			index_ = y * cols_ + x;
			if (tiles_[y][x] != EMPTY_TILE) {
				sprites_[tiles_[y][x] - 1]->SetPosition(Vector2(x * 50.0f, y * 50.0f));
				sprites_[tiles_[y][x] - 1]->Draw();
			}
		}
	}
}

// コンストラクタ: ボードの初期化
Puzzle15::Puzzle15(int rows, int cols) : row_(rows), col_(cols), moveCount_(0) {
	// タイルの数を設定し、初期値を割り当てる
	tiles_.resize(rows, std::vector<int>(cols));
	initialTiles_.resize(rows * cols);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			tiles_[i][j] = i * cols + j + 1;
			initialTiles_[i * cols + j] = i * cols + j + 1;
		}
	}

	// 空白のタイルを最後の要素に設定
	tiles_[rows - 1][cols - 1] = EMPTY_TILE;
	initialTiles_[rows * cols - 1] = EMPTY_TILE;

	// 空白のタイルのインデックスを設定
	emptyIndex_ = rows * cols - 1;
	initialEmptyIndex_ = rows * cols - 1;

	// スプライトとテクスチャの初期化
	sprites_.resize(rows * cols);
	textures_.resize(rows * cols);
	for (int i = 0; i < rows * cols - 1; i++) {
		sprites_[i] = new Sprite();
		textures_[i] = TextureManager::Load("puzzle15_Tile/tile" + std::to_string(i + 1) + ".png");
		sprites_[i]->SetTextureHandle(textures_[i]);
	}

	// タイルをシャッフル
	Shuffle();
}

// タイルをシャッフルする関数
void Puzzle15::Shuffle() {
	
	// 乱数生成器の初期化
	std::random_device rd;
	std::mt19937 g(rd());

	// 1次元ベクトルに変換してシャッフル
	std::vector<int> flatTiles;
	for (const auto& row : tiles_) {
		flatTiles.insert(flatTiles.end(), row.begin(), row.end());
	}

	// タイルをランダムにシャッフル
	std::shuffle(flatTiles.begin(), flatTiles.end(), g);

	 // 2次元ベクトルに戻す
	for (int i = 0; i < this->row_; ++i) {
		for (int j = 0; j < this->col_; ++j) {
			tiles_[i][j] = flatTiles[i * this->col_ + j];
		}
	}

	// シャッフル後の空白のタイルのインデックスを更新
	emptyIndex_ = (int)std::distance(flatTiles.begin(), std::find(flatTiles.begin(), flatTiles.end(), EMPTY_TILE));
	emptyRow_ = emptyIndex_ / this->col_;
	emptyCol_ = emptyIndex_ % this->col_; 

	// 移動回数をリセット
	ResetMoveCount();

	//移動履歴をクリア
	while (!moveHistory_.empty()) {
		moveHistory_.pop();
	}
}

// タイルを移動する関数
bool Puzzle15::MoveTile(int index) {
	// 選択されたタイルの行と列を計算
	int targetRow = index / col_;
	int targetCol = index % col_;
	// 空白のタイルの行と列を計算
	emptyRow_ = emptyIndex_ / this->col_;
	emptyCol_ = emptyIndex_ % this->col_;

	// タイルが同じ行または同じ列にある場合に移動を許可
	if (targetRow == emptyRow_) {
		// 同じ行にある場合
		if (targetCol < emptyCol_) {
			// 左側にある場合
			for (int i = emptyCol_; i > targetCol; --i) {
				std::swap(tiles_[emptyRow_][i], tiles_[emptyRow_][i - 1]);
			}
		} else if (targetCol > emptyCol_) {
			// 右側にある場合
			for (int i = emptyCol_; i < targetCol; ++i) {
				std::swap(tiles_[emptyRow_][i], tiles_[emptyRow_][i + 1]);
			}
		}
		moveHistory_.push({emptyIndex_, index});
		emptyIndex_ = index;
		moveCount_++;
		return true;
	} else if (targetCol == emptyCol_) {
		// 同じ列にある場合
		if (targetRow < emptyRow_) {
			// 上側にある場合
			for (int i = emptyRow_; i > targetRow; --i) {
				std::swap(tiles_[i][emptyCol_], tiles_[i - 1][emptyCol_]);
			}
		} else if (targetRow > emptyRow_) {
			// 下側にある場合
			for (int i = emptyRow_; i < targetRow; ++i) {
				std::swap(tiles_[i][emptyCol_], tiles_[i + 1][emptyCol_]);
			}
		}
		moveHistory_.push({emptyIndex_, index});
		emptyIndex_ = index;
		moveCount_++;
		return true;
	}

	return false;
}

// 最後の移動を元に戻す関数
void Puzzle15::UndoMove() {
	if (!moveHistory_.empty()) {
		auto [prevEmptyIndex, prevTileIndex] = moveHistory_.top();
		moveHistory_.pop();
		std::swap(tiles_[emptyIndex_ / cols_][emptyIndex_ % cols_], tiles_[prevEmptyIndex / cols_][prevEmptyIndex % cols_]);
		emptyIndex_ = prevEmptyIndex;
		moveCount_--;
	}
}

// ヒューリスティック関数
// 問題の正確な解決策がない場合や解決策を取得する時間が長すぎる場合に、問題を解決するためのショートカットとして使用される関数
int Puzzle15::Heuristic(const std::vector<int>& state) {
	int h = 0;
	for (int i = 0; i < state.size(); ++i) {
		if (state[i] != EMPTY_TILE) {
			int targetRow = (state[i] - 1) / col_;
			int targetCol = (state[i] - 1) % col_;
			int currentRow = i / col_;
			int currentCol = i % col_;
			h += std::abs(targetRow - currentRow) + std::abs(targetCol - currentCol);
		}
	}
	return h;
}

//最短手数を計算する関数
 int Puzzle15::CalculateMinimumMoves() {
	std::priority_queue<std::pair<int, std::vector<int>>, std::vector<std::pair<int, std::vector<int>>>, std::greater<>> pq;
	std::unordered_set<std::vector<int>, VectorHash> visited;
	std::vector<int> flatTiles;

	for (const auto& row : tiles_) {
		flatTiles.insert(flatTiles.end(), row.begin(), row.end());
	}

	pq.push({Heuristic(flatTiles), flatTiles});
	visited.insert(flatTiles);

	while (!pq.empty()) {
		auto [cost, state] = pq.top();
		pq.pop();

		if (std::is_sorted(state.begin(), state.end() - 1) && state.back() == EMPTY_TILE) {
			return cost;
		}

		emptyIndex_ = (int)std::distance(state.begin(), std::find(state.begin(), state.end(), EMPTY_TILE));
		emptyRow_ = emptyIndex_ / col_;
		emptyCol_ = emptyIndex_ % col_;

		std::vector<std::pair<int, int>> directions = {
		    {-1, 0 },
             {1,  0 },
             {0,  -1},
             {0,  1 }
         };
		for (auto [dr, dc] : directions) {
			int newRow = emptyRow_ + dr;
			int newCol = emptyCol_ + dc;
			if (newRow >= 0 && newRow < row_ && newCol >= 0 && newCol < col_) {
				std::vector<int> newState = state;
				std::swap(newState[emptyRow_ * col_ + emptyCol_], newState[newRow * col_ + newCol]);
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

	if (IsSolved()) {
		ImGui::Text("Congratulations! The puzzle is solved!");
	}

	// ボードのタイルを表示
	for (int y = 0; y < row_; y++) {
		for (int x = 0; x < col_; x++) {
			// タイルが空白でない場合、ボタンとして表示
			if (tiles_[y][x] != EMPTY_TILE) {
				if (ImGui::Button(std::to_string(tiles_[y][x]).c_str(), ImVec2(50, 50))) {
					// ボタンがクリックされたらタイルを移動
					MoveTile(y * this->col_ + x);
				}
			} else {
				// 空白のタイルは空白のボタンとして表示
				ImGui::Button(" ", ImVec2(50, 50));
			}

			// 右端のタイル以外は横に並べる
			if (x < this->col_ - 1)
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
	if (ImGui::Button("Reverse")) {
		UndoMove();
	}

	// 移動回数を表示
	ImGui::Text("Move Count: %d", moveCount_);

	ImGui::End();
}

//パズルが解けたかどうかを確認する関数
bool Puzzle15::IsSolved() {
	for (int i = 0; i < row_ * col_ - 1; ++i) {
		if (tiles_[i / col_][i % col_] != i + 1) {
			return false;
		}
	}
	return tiles_[row_ - 1][col_ - 1] == EMPTY_TILE;
}

//タイルを任意の場所に配置する関数
void Puzzle15::PlaceTile(int index, int value) {
	tiles_[index / col_][index % col_] = value;
	if (value == EMPTY_TILE) {
		emptyIndex_ = index;
	}
}

//パズルを初期化状態にリセットする関数
void Puzzle15::Reset() {
	
	for (int i = 0; i < row_; ++i) {
		for (int j = 0; j < col_; ++j) {
			tiles_[i][j] = initialTiles_[i * col_ + j];
		}
	}

	emptyIndex_ = initialEmptyIndex_;
	//移動回数をリセット
	ResetMoveCount();
	//移動履歴をクリア
	while (!moveHistory_.empty()) {
		moveHistory_.pop();
	}
}

//移動回数をリセットする関数
void Puzzle15::ResetMoveCount() { moveCount_ = 0; }




// スライドパズルを表示する関数
void Puzzle15::ShowSliderPuzzle() { ImGuiX(); }

void Puzzle15::HandleInput() {
	if (input_ == nullptr)
		return;

	if (input_->TriggerKey(DIK_UP)) {
		if (emptyRow_ < rows_ - 1) {
			MoveTile((emptyRow_ + 1) * cols_ + emptyCol_);
		}
	} else if (input_->TriggerKey(DIK_DOWN)) {
		if (emptyRow_ > 0) {
			MoveTile((emptyRow_ - 1) * cols_ + emptyCol_);
		}
	} else if (input_->TriggerKey(DIK_LEFT)) {
		if (emptyCol_ < cols_ - 1) {
			MoveTile(emptyRow_ * cols_ + (emptyCol_ + 1));
		}
	} else if (input_->TriggerKey(DIK_RIGHT)) {
		if (emptyCol_ > 0) {
			MoveTile(emptyRow_ * cols_ + (emptyCol_ - 1));
		}
	}
}

