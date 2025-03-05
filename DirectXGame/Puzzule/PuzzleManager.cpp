#include "PuzzleManager.h"
#include "PuzzleCollection/PuzzleCollection.h"

//
void PuzzleManager::Initialize() {
	camera_ = new Camera();
	camera_->Initialize();

	puzzleCollection_ = new PuzzleCollection();
	puzzleCollection_->Initialize();
}

void PuzzleManager::Update() {

	// カメラの更新
	camera_->TransferMatrix();

	puzzleCollection_->Update();
}

void PuzzleManager::Draw() {
	puzzleCollection_->Draw();
}

void PuzzleManager::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::DragFloat3("cameraPos", &camera_->rotation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}
