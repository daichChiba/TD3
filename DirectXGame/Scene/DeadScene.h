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
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// サウドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	uint32_t deadTexture_ = 0;
	Sprite* deadSprite_ = nullptr;
	uint32_t pushTexture_ = 0;
	Sprite* pushSprite_ = nullptr;
};
