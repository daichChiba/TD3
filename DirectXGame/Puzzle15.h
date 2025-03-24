#pragma once

#include "KamataEngine.h"
#include <d3d11.h>
#include <imgui.h>
#include <queue> //列
#include <stack>
#include <unordered_set> //順序なしセット
#include <vector>

using namespace KamataEngine;
//enum class Puzzle15Panel {
//	kZero,
//	kOne,
//	kTwo,
//	kThree,
//	kFour,
//	kFive,
//	kSix,
//	kSeven,
//	kEight,
//};
////
////
//struct Puzzle15PanelData {
//	std::vector<std::vector<Puzzle15Panel>> data;
//};
//
//class Puzzle15 {
//public:
//	 ブロックのサイズ
//	static inline const float kPanelWidth = 1.0f;
//	static inline const float kPanelHeight = 1.0f;
//	 ブロックの個数
//	static inline const uint32_t kNumPanelVirtical = 20;
//	static inline const uint32_t kNumPanelHorizontal = 100;
//
//	uint32_t GetNumPanelVirtical() const { return kNumPanelVirtical; }
//	uint32_t GetNumPanelHorizontal() const { return kNumPanelHorizontal; }
//	void ResetPuzzle15PanelData();
//
//	void LoadPuzzle15Csv(const std::string& filePath);
//	Puzzle15Panel GetPuzzle15TypeByIndex(uint32_t xIndex, uint32_t yIndex);
//	Vector3 GetPuzzle15PositionByIndex(uint32_t xIndex, uint32_t yIndex);
//
//	void Draw();
//
//private:
//	Puzzle15PanelData puzzle15PanelData_;
//	
//};

class Puzzle15 {

	public:
	// ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	uint32_t GetNumBlockVirtical() const { return kNumBlockVirtical; }
	uint32_t GetNumBlockHorizontal() const { return kNumBlockHorizontal; }
	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);
	//Puzzle15Panel GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

private:
	//Puzzle15PanelData Puzzle15PanelData_;


public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Draw();

	// コンストラクタ: ボードの初期化
	Puzzle15(int row, int col);

	// タイルをシャッフルする関数
	void Shuffle();

	// タイルを移動する関数
	bool MoveTile(int index);

	// ImGuiを使用してスライドパズルを描画する関数
	void ImGuiX();

	// パズルが解けたかどうかを確認するメソッド
	bool IsSolved();

	// タイルを任意の位置に配置するメソッド
	void PlaceTile(int index, int value);

	// パズルを初期状態にリセットするメソッド
	void Reset();

	// 移動回数をリセットするメソッド
	void ResetMoveCount();

	// 最短手数を計算するメソッド
	int CalculateMinimumMoves();

	// 最後の移動を元に戻すメソッド
	void UndoMove();

	// スライドパズルを表示する関数
	void ShowSliderPuzzle();

	// ユーザー入力を処理する関数
	void HandleInput();

public:
	// タイルの状態を保持するベクトル (2次元配列)
	std::vector<std::vector<int>> tiles_;
	// 初期状態を保存するためのベクター (1次元配列)
	std::vector<int> initialTiles_;
	// 移動履歴を保存するスタック (移動前の空白タイルのインデックス、移動後の空白タイルのインデックス)
	std::stack<std::pair<int, int>> moveHistory_;
	// スプライト描画用のメンバ変数
	std::vector<Sprite*> sprites_;
	std::vector<uint32_t> textures_;

private:
	// ヒューリスティック関数(移動履歴保存)
	int Heuristic(const std::vector<int>& state);

private:
	// 空白のタイルの値
	static const int EMPTY_TILE = 0;

	// 行数
	int rows_;
	// 列数
	int cols_;
	// インデックス
	int index_;

	// 最小移動数
	int minMoves;

	// 空白のタイルの行
	int emptyRow_;
	// 空白のタイルの列
	int emptyCol_;

	// 入力
	Input* input_ = nullptr;

	

	// Puzzle15クラスのポインタ
	Puzzle15* puzzle15_;

	// 移動回数をカウントするメンバ変数
	int moveCount_;
	// 初期状態の空白タイルのインデックス
	int initialEmptyIndex_;
	// 現在の空白のタイルのインデックス
	int emptyIndex_;
	// 選択されたタイルの行
	int row_;
	// 選択されたタイルの列
	int col_;
};