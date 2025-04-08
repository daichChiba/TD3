#include "PuzzleScene.h"

PuzzleScene::PuzzleScene()
{
}

PuzzleScene::~PuzzleScene()
{
}

void PuzzleScene::Initialize() {
	dxCommon_ =  DirectXCommon::GetInstance();

}

void PuzzleScene::Update() {
	if (Input::GetInstance()->ReleseKey(DIK_RETURN)) {
		finished_ = true;
	}
	DrawImGui();
}

void PuzzleScene::Draw() {}

void PuzzleScene::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("PuzzleScene");
	ImGui::Text("PuzzleScene");
	ImGui::End();
#endif
}
