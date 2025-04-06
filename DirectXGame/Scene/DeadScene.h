#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;


class DeadScene {
public:
	void Initialize();
	void Update();
	void Draw();

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

	// 終了フラグ
	bool finished_ = false;

private:
	void DrawImGui();
};
