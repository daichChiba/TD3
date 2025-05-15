#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "../Puzzule/BasePuzzle/BasePuzzle.h"
#include "../Puzzule/BasePuzzle/puzzles/PuzzleFactory.h"
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

	void SpriteDraw();

	/// <summary>
	/// ゲームシーンの設定
	/// </summary>
	/// <param name="gameScene"></param>
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	/// <summary>
	/// パズルの作成
	/// </summary>
	void CreatePuzzle();

	/// <summary>
	/// パズルの開始
	/// </summary>
	void StartPuzzle() ;
	/// <summary>
	/// パズルの終了
	/// </summary>
	void EndPuzzle();

private:

	GameScene* gameScene_ ;
	Camera* camera_;
	/// <summary>
	/// puzzleManagerのImGui描画
	/// </summary>
	void DrawImGui();

	// ベースパズル
	std::unique_ptr<BasePuzzle> puzzle_;
	// パズルファクトリー
	std::unique_ptr<PuzzleFactory> factory_;


};
