#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;

class ClearScene {
public:
	//ClearScene();
	//~ClearScene();

	void Initialize();
	void Update();
	void Draw();

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

	// 終了フラグ
	bool finished_ = false;

private:
	void DrawImGui();

	// サウドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t clearTexture_ = 0;
	Sprite* clearSprite_ = nullptr;
	uint32_t pushTexture_ = 0;
	Sprite* pushSprite_ = nullptr;
};
