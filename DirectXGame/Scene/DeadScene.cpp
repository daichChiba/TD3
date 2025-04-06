#include "DeadScene.h"

void DeadScene::Initialize() {}

void DeadScene::Update() {
	if (Input::GetInstance()->ReleseKey(DIK_RETURN)) {
		finished_ = true;
	}
	DrawImGui();
}

void DeadScene::Draw() {}

void DeadScene::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("DeadScene");
	ImGui::Text("DeadScene");
	ImGui::End();
#endif
}
