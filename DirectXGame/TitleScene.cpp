#include "TitleScene.h"

void TitleScene::Initialize() {}

void TitleScene::Update() {
	if (Input::GetInstance()->ReleseKey(DIK_RETURN)) {
		finished_ = true;
	}
	DrawImGui();
}

void TitleScene::Draw() {

}

void TitleScene::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("TitleScene");
	ImGui::Text("TitleScene");
	ImGui::End();
#endif
}
