#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
class BasePuzzle {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

protected:
	/// <summary>
	/// ImGuiの描画
	/// </summary>
	virtual void DrawImGui() { return; };

};
