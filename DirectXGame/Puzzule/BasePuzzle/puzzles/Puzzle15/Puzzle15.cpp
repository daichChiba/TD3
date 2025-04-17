#include "Puzzle15.h"

Puzzle15::Puzzle15() {}

Puzzle15::~Puzzle15() {}

void Puzzle15::Initialize() {
	// random_deviceを使用してシードを生成
	std::random_device rd;
	// 乱数生成器を初期化
	randomSeed.seed(rd());


	panelTextures_.push_back(TextureManager::Load("Puzzle15/panel.png"));
	for (int i = 1; i <= 15; i++) {
		panelTextures_.push_back(TextureManager::Load("Puzzle15/puzzle15_" + std::to_string(i) + ".png"));
	}
	for (size_t i = 0; i < 16; i++) {
		PanelDate panelData;
		panelData.date = static_cast<PanelType>(i);
		std::uniform_real_distribution<float> randomX(0.0f, 1080.0f);
		std::uniform_real_distribution<float> randomY(0.0f, 600.0f);
		panelData.pos = {randomX(randomSeed), randomY(randomSeed)};
		//panelData.pos = {0.0f, 0.0f};
		Sprite* panelDate= Sprite::Create(panelTextures_[i], panelData.pos);
		panelDate->SetAnchorPoint(Vector2(0.5f, 0.5f));
		panelData.sprite = panelDate;
		panelData_.push_back(panelData);
	}

	BasePuzzle::Initialize();
}

void Puzzle15::Update() {
	mousePos = input_->GetMousePosition();
	DrawImGui();
}

void Puzzle15::Draw() {

}

void Puzzle15::SpriteDraw() {
	for (size_t i = 0; i < panelData_.size(); i++) {
		panelData_[i].sprite->Draw();
	}
}



void Puzzle15::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("puzzle15");
	ImGui::Text("puzzle15,UpDate,OK");
	ImGui::DragFloat2("mousePos", &mousePos.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}
