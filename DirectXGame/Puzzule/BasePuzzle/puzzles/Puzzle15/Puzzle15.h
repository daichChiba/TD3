#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "../../BasePuzzle.h"
#include <random>
class Puzzle15 : public BasePuzzle {
public:
	Puzzle15();
	~Puzzle15();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void SpriteDraw() override;

private:
	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui() override;

private:
	// 乱数シード
	std::mt19937 randomSeed;

};
