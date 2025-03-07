#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "../../BasePuzzle.h"
class Puzzle15 : public BasePuzzle{
public:
	Puzzle15();
	~Puzzle15();
	void Update() override;	
	void Draw() override;

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui() override;

private:
	WorldTransform* worldTransform_;
};
