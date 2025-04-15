#include "Puzzle15.h"

Puzzle15::Puzzle15() {}

Puzzle15::~Puzzle15() {}

void Puzzle15::Initialize() {
	// random_deviceを使用してシードを生成
	std::random_device rd;
	// 乱数生成器を初期化
	randomSeed.seed(rd());

	BasePuzzle::Initialize();
}

void Puzzle15::Update() {
	mousePos = input_->GetMousePosition();
	DrawImGui();
}

void Puzzle15::Draw() {

}



void Puzzle15::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("puzzle15");
	ImGui::Text("puzzle15,UpDate,OK");
	ImGui::DragFloat2("mousePos", &mousePos.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}
