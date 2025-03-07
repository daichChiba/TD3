#include "PuzzleManager.h"
#include "BasePuzzle/BasePuzzle.h"
#include "../Puzzule/BasePuzzle/puzzles/PuzzleFactory.h"

void PuzzleManager::Initialize() {
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

void PuzzleManager::Draw() {
	puzzle_->Draw();
}

void PuzzleManager::CreatePuzzle() {
	puzzle_ = factory_->CreatePuzzle15();
	puzzle_->Initialize();
}

void PuzzleManager::StartPuzzle() {
	CreatePuzzle();
}

void PuzzleManager::EndPuzzle() {
	puzzle_.reset();
}

void PuzzleManager::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::DragFloat3("cameraPos", &camera_->rotation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}
