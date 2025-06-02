#include <Windows.h>
#include <KamataEngine.h>
using namespace KamataEngine;
#include "Scene/ClearScene.h"
#include "Scene/DeadScene.h"
#include "Scene/GameScene.h"
#include "Scene/PuzzleScene.h"
#include "Scene/RuleScene.h"
#include "Scene/TitleScene.h"

// シーン（型）
enum class Scene {
	kUnknown = 0,
	kTitle,
	kRule,
	kPuzzle,
	kGame,
	kClear,
	kDead,
};

// 現在シーン（型）
Scene scene = Scene::kUnknown;

void CenterMouseCursor(HWND hwnd);

void ChangeScene();
void UpdateScene();
void DrawScene();

GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;
RuleScene* ruleScene = nullptr;
PuzzleScene* puzzleScene = nullptr;
ClearScene* clearScene = nullptr;
DeadScene* deadScene = nullptr;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;

	// GameScene* gameScene = new GameScene;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow();

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化

	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();

#pragma endregion

	// ゲームシーンの初期化
	titleScene = new TitleScene();
	titleScene->Initialize();
	scene = Scene::kTitle;

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		//if (Input::GetInstance()->TriggerKey(DIK_P)) {
		//	debugFulag = !debugFulag;
		//}
		if (scene == Scene::kGame) {
			// マウスカーソルをウィンドウ中央に固定
			CenterMouseCursor(win->GetHwnd());
		}
		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)){
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		ChangeScene();
		UpdateScene();

		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		DrawScene();
		// 軸表示の描画
		axisIndicator->Draw();

		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete titleScene;
	delete ruleScene;
	delete gameScene;
	delete puzzleScene;
	delete clearScene;
	delete deadScene;

	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}

void CenterMouseCursor(HWND hwnd) {
	RECT rect;
	if (GetWindowRect(hwnd, &rect)) {
		int centerX = (rect.left + rect.right) / 2;
		int centerY = (rect.top + rect.bottom) / 2;
		SetCursorPos(centerX, centerY);
	}
}

// シーン切り替え
void ChangeScene() {

	switch (scene) {
	case Scene::kTitle:

		if (titleScene->IsFinished()) {
			if (!titleScene->IsRule()) {
				// シーン変更
				scene = Scene::kGame;
				// 旧シーンの開放
				delete titleScene;
				titleScene = nullptr;
				// 新シーンの生成と初期化
				gameScene = new GameScene;
				gameScene->Initialize();
			} else {
				if (titleScene->IsRule()) {
					scene = Scene::kRule;
					delete titleScene;
					titleScene = nullptr;
					ruleScene = new RuleScene;
					ruleScene->Initialize();
				}
			}
		} 
		break;
	case Scene::kRule:
		if (ruleScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧シーンの開放
			delete ruleScene;
			ruleScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	case Scene::kPuzzle:
		if (puzzleScene->IsFinished()) {
			// シーン変更
			scene = Scene::kGame;
			// 旧シーンの開放
			delete puzzleScene;
			puzzleScene = nullptr;
			// 新シーンの生成と初期化
			if (gameScene->IsFinished()) {
				gameScene = new GameScene;
				gameScene->Initialize();
			}
			if (gameScene->IsStop()) {
				gameScene->SetIsStop();
				gameScene->puzzleClear = true;
			}
		} // else if (mobScene->HP <= 0) {
		//	// シーン変更
		//	scene = Scene::kDead;
		//	// 旧シーンの開放
		//	delete mobScene;
		//	mobScene = nullptr;
		//	// 新シーンの生成と初期化
		//	deadScene = new DeadScene;
		//	deadScene->Initialize();
		//}

		break;
	case Scene::kGame:
		if (gameScene->IsStop()) {
			// シーン変更
			scene = Scene::kPuzzle;
			delete puzzleScene;
			puzzleScene = new PuzzleScene;
			puzzleScene->Initialize();
		}
		if (gameScene->IsFinished()) {
			if (gameScene->IsClear()) {
				scene = Scene::kClear;
				delete gameScene;

				clearScene = new ClearScene;
				clearScene->Initialize();
			}
		}
		if (gameScene->DeadFinished_) {
			scene = Scene::kDead;
			delete gameScene;

			deadScene = new DeadScene;
			deadScene->Initialize();
		}

		break;
	case Scene::kClear:
		if (clearScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧シーンの開放
			delete clearScene;
			clearScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	case Scene::kDead:
		if (deadScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧シーンの開放
			delete deadScene;
			deadScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
	}
}

// 現在シーン更新
void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kRule:
		ruleScene->Update();
		break;
	case Scene::kPuzzle:
		puzzleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	case Scene::kClear:
		clearScene->Update();
		break;
	case Scene::kDead:
		deadScene->Update();
		break;
	}
}

// 現在シーンの描画
void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kRule:
		ruleScene->Draw();
		break;
	case Scene::kPuzzle:
		puzzleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	case Scene::kClear:
		clearScene->Draw();
		break;
	case Scene::kDead:
		deadScene->Draw();
		break;
	}
}