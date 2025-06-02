#include "PuzzleManager.h"
#include "../Puzzule/BasePuzzle/puzzles/PuzzleFactory.h"
#include "BasePuzzle/BasePuzzle.h"

void PuzzleManager::Initialize() {

	// random_deviceを使用してシードを生成
	std::random_device rd;
	// 乱数生成器を初期化
	randomSeed.seed(rd());
	// 乱数生成器の初期化
	std::uniform_int_distribution<int> random(1, 2);
	// 乱数を生成
	randomNum = random(randomSeed);

	camera_ = new Camera();
	camera_->Initialize();
	factory_ = std::make_unique<PuzzleFactory>();
	CreatePuzzle();
}

void PuzzleManager::Update() {

	// カメラの更新
	camera_->TransferMatrix();

	puzzle_->Update();
}

void PuzzleManager::Draw() { puzzle_->Draw(); }

void PuzzleManager::SpriteDraw() { puzzle_->SpriteDraw(); }

void PuzzleManager::CreatePuzzle() {
	if (randomNum == 1) {
		puzzle_ = factory_->CreatePuzzle15();
		puzzle_->Initialize();
	}
	if (randomNum == 2) {
		puzzle_ = factory_->CreateCircuitPuzzle();
		puzzle_->Initialize();
	}
}

void PuzzleManager::StartPuzzle() { CreatePuzzle(); }

void PuzzleManager::EndPuzzle() { puzzle_.reset(); }

bool PuzzleManager::GetIsClear() { return puzzle_->GetIsClear(); }

void PuzzleManager::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::DragFloat3("cameraPos", &camera_->rotation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}
