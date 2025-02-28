#pragma once

#include <vector>
#include <imgui.h>
#include "KamataEngine.h"
using namespace KamataEngine;

class Board {
public:
	// コンストラクタ: ボードの初期化
	Board();
	
	// タイルを移動する関数
	bool MoveTile(int index);

	// スライドパズルを表示する関数
	void ShowSliderPuzzle();

	// ImGuiを使用してスライドパズルを描画する関数
	void ImGuiX();

	//パズルが解けたか同化を確認するメソッド
	bool IsSolved();

	void Clear();

	//タイルを任意の位置に配置するメソッド
	void PlaceTile(int index, int value);

private:
	// ボードのサイズ
	static const int SIZE = 3;

	// タイルの状態を保持するベクトル
	std::vector<int> tiles;

	// 空白のタイルの値
	static const int EMPTY_TILE = 0;

	// 空白のタイルのインデックス
	int emptyIndex;

	// タイルをシャッフルする関数
	void Shuffle();

	// 選択されたタイルの行
	int row;

	// 空白のタイルの行
	int emptyRow;

	// 選択されたタイルの列
	int col;

	// 空白のタイルの列
	int emptyCol;

	Input* input_ = nullptr;
};