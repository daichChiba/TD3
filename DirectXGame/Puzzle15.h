#pragma once

#include <vector>
#include <imgui.h>
#include <stack>
#include <queue>//列
#include <unordered_set>//順序なしセット
#include <d3d11.h>
#include "KamataEngine.h"
using namespace KamataEngine;

class Puzzle15 {
public:
	// コンストラクタ: ボードの初期化
	Puzzle15(int row, int col);

	void Update();

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

public:

	// 移動回数をカウントするメンバ変数
	int moveCount_;
	// 初期状態の空白タイルのインデックス
	int initialEmptyIndex_;
	// 空白のタイルのインデックス
	int emptyIndex_;
	// 選択されたタイルの行
	int row_;
	// 選択されたタイルの列
	int col_;

	

	// タイルの状態を保持するベクトル
	std::vector<std::vector<int>> tiles_;
	// 初期状態を保存するためのベクター
	std::vector<int> initialTiles_; 
	//移動履歴を保存するスタック
	std::stack<std::pair<int, int>> moveHistory_;


private:

	// ヒューリスティック関数(移動履歴保存)
	int Heuristic(const std::vector<int>& state);

	// 空白のタイルの値
	static const int EMPTY_TILE = 0;

	int rows_;
	int cols_;
	int index_;
	
	int minMoves;

	// 空白のタイルの行
	int emptyRow_;
	// 空白のタイルの列
	int emptyCol_;

	Input* input_ = nullptr;

};
