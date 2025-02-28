#pragma once

#include <vector>
#include <imgui.h>
#include "KamataEngine.h"
using namespace KamataEngine;

class Board {
public:

	// 選択されたタイルの行
	int row;

	// 選択されたタイルの列
	int col;

	// タイルの状態を保持するベクトル
	std::vector<int> tiles;

	// 初期状態を保存するためのベクター
	 std::vector<int> initialTiles; 

	 // 初期状態の空白タイルのインデックス
	int initialEmptyIndex;        

	//移動回数をカウントするメンバ変数
	int moveCount = 0;

public:
	// コンストラクタ: ボードの初期化
	Board(int row, int col);
	
	// タイルを移動する関数
	bool MoveTile(int index);

	// スライドパズルを表示する関数
	void ShowSliderPuzzle();

	// ImGuiを使用してスライドパズルを描画する関数
	void ImGuiX();

	// パズルが解けたかどうかを確認するメソッド
	 bool IsSolved();                      

	//タイルを任意の位置に配置するメソッド
	void PlaceTile(int index, int value);

	// パズルを初期状態にリセットするメソッド
	void Reset(); 

	//移動回数をリセットするメソッド
	void ResetMoveCount();

private:

	// 空白のタイルの値
	static const int EMPTY_TILE = 0;

	// 空白のタイルのインデックス
	int emptyIndex;

	// タイルをシャッフルする関数
	void Shuffle();

	int rows;

	int cols;

	// 空白のタイルの行
	int emptyRow;

	// 空白のタイルの列
	int emptyCol;

	Input* input_ = nullptr;

};
