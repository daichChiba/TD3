#pragma once
#include "../../BasePuzzle.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

enum class PanelType {
	Block,
	Panel,
};

struct PanelData {
	std::vector<std::vector<PanelType>> date;
};

class CircuitPuzzle : public BasePuzzle {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CircuitPuzzle();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CircuitPuzzle();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private:
	void DrawImGui() override;

private:
	PanelData panelData_;


};
