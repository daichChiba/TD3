#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "../../BasePuzzle.h"
#include <iostream>
#include <random>
#include <vector>

class Puzzle15 : public BasePuzzle {
public:
	enum class PanelType {
		Blank,
		panel1,
		panel2,
		panel3,
		panel4,
		panel5,
		panel6,
		panel7,
		panel8,
		panel9,
		panel10,
		panel11,
		panel12,
		panel13,
		panel14,
		panel15
	};
	struct PanelDate {
		PanelType date;
		Sprite* sprite;
		Vector2 pos;
	};
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
	// パネルのテクスチャ
	std::vector<uint32_t> panelTextures_;
	// パネルデータ
	std::vector<PanelDate> panelData_;
};
