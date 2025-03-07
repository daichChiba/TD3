#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include <iostream>
#include <vector>

enum Level {
	Normal,
	Hard,
	Extra,
};

class BasePuzzle {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();


protected:
	//難易度
	Level level_;
	Vector2 mousePos;

	Input* input_;


	/// <summary>
	/// ImGuiの描画
	/// </summary>
	virtual void DrawImGui() { return; };
};
