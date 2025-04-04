#include "ClearScene.h"

void ClearScene::Initialize() {}

void ClearScene::Update() {
	if (Input::GetInstance()->ReleseKey(DIK_RETURN)) {
		finished_ = true;
	}
	DrawImGui();
}
void ClearScene::Draw() {}

void ClearScene::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("ClearScene");
	ImGui::Text("ClearScene");
	ImGui::End();
#endif
}
