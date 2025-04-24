#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;

//ルール説明のシーン
class RuleScene {
public:
	void Initialize();
	void Update();
	void Draw();

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

private:
	// 終了フラグ
	bool finished_ = false;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t ruleTexture_ = 0;
	Sprite* ruleSprite_ = nullptr;

};
