#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "../../BasePuzzle.h"

class OneStrokePuzzle : public BasePuzzle {
public:
	OneStrokePuzzle();
	~OneStrokePuzzle();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui() override;
};
