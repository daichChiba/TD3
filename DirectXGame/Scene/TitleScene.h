#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;


class TitleScene {
public:
	void Initialize();
	void Update();
	void Draw();

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }
	bool IsRule() const { return isRule_; }
	

private:
	// 終了フラグ
	bool finished_ = false;
	bool isRule_ = false;

	void DrawImGui();
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// サウドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	uint32_t titleTexture_ = 0;
	Sprite* titleSprite_ = nullptr;

};
