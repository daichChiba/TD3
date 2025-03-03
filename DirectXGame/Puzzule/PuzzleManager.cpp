#include "PuzzleManager.h"

void PuzzleManager::Initialize() {
	camera_ = new Camera();
	camera_->Initialize();
}

void PuzzleManager::Update() {
	DrawImGui();
}

void PuzzleManager::Draw() {

}

void PuzzleManager::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::DragFloat3("cameraPos", &camera_->rotation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}
