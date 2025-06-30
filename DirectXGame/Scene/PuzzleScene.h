#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "../Puzzule/PuzzleManager.h"

class PuzzleScene {
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
	// パズルマネージャー
	PuzzleManager* puzzleManager_ = nullptr;

	// サウドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
};
