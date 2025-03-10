#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include <vector>
#include "../Puzzle15.h"

class GameScene {
public:
	// メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void GeneratePanels();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	Audio* audio_ = nullptr;

	std::vector<std::vector<WorldTransform*>> worldTransformPanels_;

	//2D背景
	Sprite* puzzle_ = nullptr;
	uint32_t slidePuzzle15_ = 0;

	Puzzle15* puzzle15_;

};
