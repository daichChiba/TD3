#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
class GameScene;

class PuzzleManager {
public:
	void Initialize();
	void Update();
	void Draw();

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:
	GameScene* gameScene_ ;
	Camera* camera_;
	void DrawImGui();
};
