#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "../Puzzule/PuzzleCollection/PuzzleCollection.h"
class GameScene;

class PuzzleManager {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ゲームシーンの設定
	/// </summary>
	/// <param name="gameScene"></param>
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:

	GameScene* gameScene_ ;
	Camera* camera_;
	/// <summary>
	/// puzzleManagerのImGui描画
	/// </summary>
	void DrawImGui();

	PuzzleCollection* puzzleCollection_;
};
