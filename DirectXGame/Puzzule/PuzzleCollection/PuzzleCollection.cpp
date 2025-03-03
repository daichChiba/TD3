#include "PuzzleCollection.h"

void PuzzleCollection::Initialize() {
#ifdef _DEBUG

#endif // _DEBUG


}

void PuzzleCollection::Update() {

}

void PuzzleCollection::Draw() {

}

void PuzzleCollection::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::Text("PuzzleCollection");
	ImGui::End();
#endif // _DEBUG
}
