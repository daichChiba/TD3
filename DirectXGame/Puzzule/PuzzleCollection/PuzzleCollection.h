#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
class PuzzleCollection {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	/// <summary>
	/// puzzleManagerのImGui描画
	/// </summary>
	void DrawImGui() { return; };
	/// <summary>
	/// パズルが完成しているか確認
	/// </summary>
	void ChackPuzzle() { return; };
};
