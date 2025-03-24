
#include "Puzzle15.h"
#include <assert.h>
#include <fstream>
#include <map>
#include <sstream>

namespace {
    std::map<std::string, Puzzle15Panel> MapChipTable = {
        {"0", Puzzle15Panel::kZero},
        {"1", Puzzle15Panel::kOne},
        {"2", Puzzle15Panel::kTwo  },
        {"3", Puzzle15Panel::kThree},
        {"4", Puzzle15Panel::kFour },
        {"5", Puzzle15Panel::kFive },
        {"6", Puzzle15Panel::kSix  },
        {"7", Puzzle15Panel::kSeven},
        {"8", Puzzle15Panel::kEight},
    };
}

void Puzzle15::ResetPuzzle15PanelData() {
	puzzle15PanelData_.data.clear();
	puzzle15PanelData_.data.resize(kNumPanelVirtical);
	for (std::vector<Puzzle15Panel>& MapChipDataLine : puzzle15PanelData_.data) {
		MapChipDataLine.resize(kNumPanelHorizontal);
	}
}

void Puzzle15::LoadPuzzle15Csv(const std::string& filePath) {
	// マップチップデータをリセット
	ResetPuzzle15PanelData();

	// ファイルを開く
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	// マップチップCSV
	std::stringstream mapChipCsv;
	// ファイルの内容を文字列ストリームにコピー
	mapChipCsv << file.rdbuf();
	// ファイルを閉じる
	file.close();

	// CSVからマップチップデータを読み込む
	for (uint32_t i = 0; i < kNumPanelVirtical; ++i) {
		std::string line;
		getline(mapChipCsv, line);

		// 1行分の文字列をストリームに変換して解析しやすくなる
		std::istringstream line_stream(line);

		for (uint32_t j = 0; j < kNumPanelHorizontal; ++j) {
			std::string word;
			getline(line_stream, word, ',');

			if (MapChipTable.contains(word)) {
				puzzle15PanelData_.data[i][j] = MapChipTable[word];
			}
		}
	}
}

Puzzle15Panel Puzzle15::GetPuzzle15TypeByIndex(uint32_t xIndex, uint32_t yIndex) {
	if (xIndex < 0 || kNumPanelHorizontal - 1 < xIndex) {
		return Puzzle15Panel::kZero;
	}
	if (yIndex < 0 || kNumPanelVirtical - 1 < yIndex) {
		return Puzzle15Panel::kZero;
	}
	return puzzle15PanelData_.data[yIndex][xIndex];
}

Vector3 Puzzle15::GetPuzzle15PositionByIndex(uint32_t xIndex, uint32_t yIndex) {
	return Vector3(kPanelWidth * xIndex, kPanelHeight * (kNumPanelVirtical - 1 - yIndex), 0);
}

 


//#include "Puzzle15.h"
//#include <algorithm>
//#include <chrono>
//#include <queue>
//#include <random>
//#include <unordered_set>
//
//// カスタムハッシュ関数を定義
//// std::unordered_set で std::vector をキーとして使うためのハッシュ関数
//struct VectorHash {
//	std::size_t operator()(const std::vector<int>& v) const {
//		std::size_t seed = v.size();
//		for (auto& i : v) {
//			seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//		}
//		return seed;
//	}
//};
//
//// 初期化処理
//void Puzzle15::Initialize() {}
//
//// 更新処理
//void Puzzle15::Update() {
//	HandleInput();
//	// Zキーが押されたら、一手戻る
//	if (input_ && input_->TriggerKey(DIK_Z)) {
//		UndoMove();
//	}
//}
//
//// 描画処理
//void Puzzle15::Draw() {
//	// 全てのタイルを描画する
//	for (int y = 0; y < rows_; y++) {
//		for (int x = 0; x < cols_; x++) {
//			index_ = y * cols_ + x;
//			// 空白タイル以外を描画
//
//			if (tiles_[y][x] != EMPTY_TILE) {
//				// タイルの位置を設定して描画
//				sprites_[tiles_[y][x] - 1]->SetPosition(Vector2(x * 10.0f, y * 10.0f));
//				sprites_[tiles_[y][x] - 1]->SetSize(Vector2(1.0f, 1.0f));
//				sprites_[tiles_[y][x] - 1]->Draw();
//			}
//		}
//	}
//}
//
//// コンストラクタ: ボードの初期化
//Puzzle15::Puzzle15(int rows, int cols) : row_(rows), col_(cols), moveCount_(0) {
//	// タイルの数を設定し、初期値を割り当てる
//	tiles_.resize(rows, std::vector<int>(cols));
//	initialTiles_.resize(rows * cols);
//	// 各タイルに初期値を設定
//	for (int i = 0; i < rows; ++i) {
//		for (int j = 0; j < cols; ++j) {
//			tiles_[i][j] = i * cols + j + 1;
//			initialTiles_[i * cols + j] = i * cols + j + 1;
//		}
//	}
//
//	// 空白のタイルを最後の要素に設定
//	tiles_[rows - 1][cols - 1] = EMPTY_TILE;
//	initialTiles_[rows * cols - 1] = EMPTY_TILE;
//
//	// 空白のタイルのインデックスを設定
//	emptyIndex_ = rows * cols - 1;
//	initialEmptyIndex_ = rows * cols - 1;
//
//	// スプライトとテクスチャの初期化
//	sprites_.resize(rows * cols);
//	textures_.resize(rows * cols);
//	// 各タイルに対応するスプライトを作成し、テクスチャを設定
//
//	for (int i = 0; i < rows * cols - 1; i++) {
//		sprites_[i] = new Sprite();
//		textures_[i] = TextureManager::Load("puzzle15_Tile/" + std::to_string(i + 1) + ".png");
//		sprites_[i]->SetTextureHandle(textures_[i]);
//	}
//
//	// タイルをシャッフル
//	Shuffle();
//}
//
//// タイルをシャッフルする関数
//void Puzzle15::Shuffle() {
//
//	// 乱数生成器の初期化
//	std::random_device rd;
//	std::mt19937 g(rd());
//
//	// 1次元ベクトルに変換してシャッフル
//	std::vector<int> flatTiles;
//	for (const auto& row : tiles_) {
//		flatTiles.insert(flatTiles.end(), row.begin(), row.end());
//	}
//
//	// タイルをランダムにシャッフル
//	std::shuffle(flatTiles.begin(), flatTiles.end(), g);
//
//	// 2次元ベクトルに戻す
//	for (int i = 0; i < this->row_; ++i) {
//		for (int j = 0; j < this->col_; ++j) {
//			tiles_[i][j] = flatTiles[i * this->col_ + j];
//		}
//	}
//
//	// シャッフル後の空白のタイルのインデックスを更新
//	emptyIndex_ = (int)std::distance(flatTiles.begin(), std::find(flatTiles.begin(), flatTiles.end(), EMPTY_TILE));
//	emptyRow_ = emptyIndex_ / this->col_;
//	emptyCol_ = emptyIndex_ % this->col_;
//
//	// 移動回数をリセット
//	ResetMoveCount();
//
//	// 移動履歴をクリア
//	while (!moveHistory_.empty()) {
//		moveHistory_.pop();
//	}
//}
//
//// タイルを移動する関数
//bool Puzzle15::MoveTile(int index) {
//	// 選択されたタイルの行と列を計算
//	int targetRow = index / col_;
//	int targetCol = index % col_;
//	// 空白のタイルの行と列を計算
//	emptyRow_ = emptyIndex_ / this->col_;
//	emptyCol_ = emptyIndex_ % this->col_;
//
//	// タイルが同じ行または同じ列にある場合に移動を許可
//	if (targetRow == emptyRow_) {
//		// 同じ行にある場合
//		if (targetCol < emptyCol_) {
//			// 左側にある場合
//			for (int i = emptyCol_; i > targetCol; --i) {
//				std::swap(tiles_[emptyRow_][i], tiles_[emptyRow_][i - 1]);
//			}
//		} else if (targetCol > emptyCol_) {
//			// 右側にある場合
//			for (int i = emptyCol_; i < targetCol; ++i) {
//				std::swap(tiles_[emptyRow_][i], tiles_[emptyRow_][i + 1]);
//			}
//		}
//		// 移動履歴に現在の状態を保存
//		moveHistory_.push({emptyIndex_, index});
//		// 空白のインデックスを更新
//		emptyIndex_ = index;
//		// 移動回数をインクリメント
//		moveCount_++;
//		return true;
//	} else if (targetCol == emptyCol_) {
//		// 同じ列にある場合
//		if (targetRow < emptyRow_) {
//			// 上側にある場合
//			for (int i = emptyRow_; i > targetRow; --i) {
//				std::swap(tiles_[i][emptyCol_], tiles_[i - 1][emptyCol_]);
//			}
//		} else if (targetRow > emptyRow_) {
//			// 下側にある場合
//			for (int i = emptyRow_; i < targetRow; ++i) {
//				std::swap(tiles_[i][emptyCol_], tiles_[i + 1][emptyCol_]);
//			}
//		}
//		// 移動履歴に現在の状態を保存
//		moveHistory_.push({emptyIndex_, index});
//		// 空白のインデックスを更新
//		emptyIndex_ = index;
//		// 移動回数をインクリメント
//		moveCount_++;
//		return true;
//	}
//
//	return false;
//}
//
//// 最後の移動を元に戻す関数
//void Puzzle15::UndoMove() {
//	// 移動履歴がある場合のみ元に戻す
//	if (!moveHistory_.empty()) {
//		// 最新の移動を取得
//		auto [prevEmptyIndex, prevTileIndex] = moveHistory_.top();
//		// 移動履歴から削除
//		moveHistory_.pop();
//		// タイルを元に戻す
//		std::swap(tiles_[emptyIndex_ / cols_][emptyIndex_ % cols_], tiles_[prevEmptyIndex / cols_][prevEmptyIndex % cols_]);
//		// 空白のインデックスを更新
//		emptyIndex_ = prevEmptyIndex;
//		// 移動回数をデクリメント
//		moveCount_--;
//	}
//}
//
//// ヒューリスティック関数
//// 問題の正確な解決策がない場合や解決策を取得する時間が長すぎる場合に、問題を解決するためのショートカットとして使用される関数
//int Puzzle15::Heuristic(const std::vector<int>& state) {
//	int h = 0;
//	for (int i = 0; i < state.size(); ++i) {
//		if (state[i] != EMPTY_TILE) {
//			int targetRow = (state[i] - 1) / col_;
//			int targetCol = (state[i] - 1) % col_;
//			int currentRow = i / col_;
//			int currentCol = i % col_;
//			h += std::abs(targetRow - currentRow) + std::abs(targetCol - currentCol);
//		}
//	}
//	return h;
//}
//
//// 最短手数を計算する関数
//int Puzzle15::CalculateMinimumMoves() {
//	// 優先度付きキュー (コスト, 状態)
//	std::priority_queue<std::pair<int, std::vector<int>>, std::vector<std::pair<int, std::vector<int>>>, std::greater<>> pq;
//	// 訪問済みの状態を保存するunordered_set
//	std::unordered_set<std::vector<int>, VectorHash> visited;
//	std::vector<int> flatTiles;
//
//	// 2次元配列を1次元配列に変換
//	for (const auto& row : tiles_) {
//		flatTiles.insert(flatTiles.end(), row.begin(), row.end());
//	}
//
//	// 初期状態をキューに追加
//	pq.push({Heuristic(flatTiles), flatTiles});
//	visited.insert(flatTiles);
//
//	// キューが空になるまで探索
//	while (!pq.empty()) {
//		// 現在の状態を取得
//		auto [cost, state] = pq.top();
//		pq.pop();
//
//		// ゴール状態に達したら、コストを返す
//		if (std::is_sorted(state.begin(), state.end() - 1) && state.back() == EMPTY_TILE) {
//			return cost;
//		}
//
//		// 空白タイルの位置を取得
//		emptyIndex_ = (int)std::distance(state.begin(), std::find(state.begin(), state.end(), EMPTY_TILE));
//		emptyRow_ = emptyIndex_ / col_;
//		emptyCol_ = emptyIndex_ % col_;
//
//		// 上下左右の移動を試す
//		std::vector<std::pair<int, int>> directions = {
//		    {-1, 0 }, // 上
//		    {1,  0 }, // 下
//		    {0,  -1}, // 左
//		    {0,  1 }  // 右
//		};
//		for (auto [dr, dc] : directions) {
//			// 新しい行と列を計算
//			int newRow = emptyRow_ + dr;
//			int newCol = emptyCol_ + dc;
//			// 新しい行と列が範囲内にあるか確認
//			if (newRow >= 0 && newRow < row_ && newCol >= 0 && newCol < col_) {
//				// 新しい状態を作成
//				std::vector<int> newState = state;
//				// 空白タイルと移動先のタイルを入れ替える
//				std::swap(newState[emptyRow_ * col_ + emptyCol_], newState[newRow * col_ + newCol]);
//				// 訪問済みでなければキューに追加
//				if (visited.find(newState) == visited.end()) {
//					pq.push({cost + 1 + Heuristic(newState), std::move(newState)});
//					visited.insert(newState);
//				}
//			}
//		}
//	}
//
//	return -1; // 解が見つからない場合
//}
//
//// ImGui を使用してスライドパズルを表示する関数
//void Puzzle15::ImGuiX() {
//	ImGui::Begin("Slide Puzzle");
//
//	// パズルが解けたかどうかのメッセージを表示
//	if (IsSolved()) {
//		ImGui::Text("Congratulations! The puzzle is solved!");
//	}
//
//	// ボードのタイルを表示
//	for (int y = 0; y < row_; y++) {
//		for (int x = 0; x < col_; x++) {
//			// タイルが空白でない場合、ボタンとして表示
//			if (tiles_[y][x] != EMPTY_TILE) {
//				// タイルの数字をボタンとして表示
//				if (ImGui::Button(std::to_string(tiles_[y][x]).c_str(), ImVec2(50, 50))) {
//					// ボタンがクリックされたらタイルを移動
//					MoveTile(y * this->col_ + x);
//				}
//			} else {
//				// 空白のタイルは空白のボタンとして表示
//				ImGui::Button(" ", ImVec2(50, 50));
//			}
//
//			// 右端のタイル以外は横に並べる
//			if (x < this->col_ - 1)
//				ImGui::SameLine();
//		}
//	}
//
//	// シャッフルボタン
//	if (ImGui::Button("Shuffle")) {
//		Shuffle();
//	}
//
//	// リセットボタン
//	if (ImGui::Button("Reset")) {
//		Reset();
//	}
//
//	// 元に戻すボタン
//	if (ImGui::Button("Reverse")) {
//		UndoMove();
//	}
//
//	// 移動回数を表示
//	ImGui::Text("Move Count: %d", moveCount_);
//
//    ImGui::DragFloat2("size", const_cast<float*>(&sprites_[1]->GetSize().x), 1.0f, 0.0f, 100.0f);
//	ImGui::DragFloat3("pos", const_cast<float*>(&sprites_[1]->GetPosition().x), 1.0f, 0.0f, 100.0f);
//
//	ImGui::End();
//}
//
//// パズルが解けたかどうかを確認する関数
//bool Puzzle15::IsSolved() {
//	// 0から(タイルの数-1)までループ
//	for (int i = 0; i < row_ * col_ - 1; ++i) {
//		// タイルの値が正しい順序になっていない場合、falseを返す
//		if (tiles_[i / col_][i % col_] != i + 1) {
//			return false;
//		}
//	}
//	// 最後のタイルが空白の場合、trueを返す
//	return tiles_[row_ - 1][col_ - 1] == EMPTY_TILE;
//}
//
//// タイルを任意の場所に配置する関数
//void Puzzle15::PlaceTile(int index, int value) {
//	// 指定されたインデックスのタイルに値を設定
//	tiles_[index / col_][index % col_] = value;
//	// 空白のタイルである場合、インデックスを更新
//	if (value == EMPTY_TILE) {
//		emptyIndex_ = index;
//	}
//}
//
//// パズルを初期化状態にリセットする関数
//void Puzzle15::Reset() {
//
//	// 初期状態を復元
//	for (int i = 0; i < row_; ++i) {
//		for (int j = 0; j < col_; ++j) {
//			tiles_[i][j] = initialTiles_[i * col_ + j];
//		}
//	}
//
//	// 空白タイルのインデックスを初期状態に戻す
//	emptyIndex_ = initialEmptyIndex_;
//	// 移動回数をリセット
//	ResetMoveCount();
//	// 移動履歴をクリア
//	while (!moveHistory_.empty()) {
//		moveHistory_.pop();
//	}
//}
//
//// 移動回数をリセットする関数
//void Puzzle15::ResetMoveCount() { moveCount_ = 0; }
//
//// スライドパズルを表示する関数
//void Puzzle15::ShowSliderPuzzle() { ImGuiX(); }
//
//// ユーザー入力を処理する関数
//void Puzzle15::HandleInput() {
//	// 入力がない場合は処理しない
//	if (input_ == nullptr)
//		return;
//
//	// 上キーが押された場合
//	if (input_->TriggerKey(DIK_UP)) {
//		// 空白タイルが一番下になければ上に移動
//		if (emptyRow_ < rows_ - 1) {
//			MoveTile((emptyRow_ + 1) * cols_ + emptyCol_);
//		}
//		// 下キーが押された場合
//	} else if (input_->TriggerKey(DIK_DOWN)) {
//		// 空白タイルが一番上でなければ下に移動
//		if (emptyRow_ > 0) {
//			MoveTile((emptyRow_ - 1) * cols_ + emptyCol_);
//		}
//		// 左キーが押された場合
//	} else if (input_->TriggerKey(DIK_LEFT)) {
//		// 空白タイルが一番右になければ左に移動
//		if (emptyCol_ < cols_ - 1) {
//			MoveTile(emptyRow_ * cols_ + (emptyCol_ + 1));
//		}
//		// 右キーが押された場合
//	} else if (input_->TriggerKey(DIK_RIGHT)) {
//		// 空白タイルが一番左になければ右に移動
//		if (emptyCol_ > 0) {
//			MoveTile(emptyRow_ * cols_ + (emptyCol_ - 1));
//		}
//	}
//}