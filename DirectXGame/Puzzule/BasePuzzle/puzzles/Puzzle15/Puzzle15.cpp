#include "Puzzle15.h"

Puzzle15::Puzzle15() {}

Puzzle15::~Puzzle15() {}

void Puzzle15::Update() {
	DrawImGui();
}

void Puzzle15::Draw() {

}



void Puzzle15::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("puzzle15");
	ImGui::Text("puzzle15,UpDate,OK");
	ImGui::End();
#endif // _DEBUG
}
