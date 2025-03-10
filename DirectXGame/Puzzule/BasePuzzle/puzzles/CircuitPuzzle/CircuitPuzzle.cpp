#include "CircuitPuzzle.h"

CircuitPuzzle::CircuitPuzzle() {

}

CircuitPuzzle::~CircuitPuzzle() {

}

void CircuitPuzzle::Initialize() {

}

void CircuitPuzzle::Update() {
	DrawImGui();
}

void CircuitPuzzle::Draw() {

}

void CircuitPuzzle::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("CircuitPuzzle");
	ImGui::Text("CircuitPuzzle,UpDate,OK");
	ImGui::End();
#endif // _DEBUG
}
