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
	ImGui::Begin("CircuitPuzzle");
	ImGui::Text("CircuitPuzzle,UpDate,OK");
	ImGui::End();
}
