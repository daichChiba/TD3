#include "Puzzle15.h"

Puzzle15::Puzzle15() {}

Puzzle15::~Puzzle15() {
	// FileAccessorの解放
	if (fileAccessor_) {
		delete fileAccessor_;
		fileAccessor_ = nullptr;
	}
}

void Puzzle15::Initialize() {
	// FileAccessorの初期化
	fileAccessor_ = nullptr;
	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/Puzzle15/Puzzle15.json");

	// JSONからパネルサイズを読み込む
	panelSize_ = fileAccessor_->ReadVector3("Puzzle15", "size", Vector3());

	// JSONからisCompleteを読み込む
	isClear_ = fileAccessor_->Read("Puzzle15", "isClear", bool());

	// JSONからCSVデータを読み込む
	csvData_ = fileAccessor_->ReadCsvData("Puzzle15", "start");
	answerData_ = fileAccessor_->ReadCsvData("Puzzle15", "answer");

	// パネルのテクスチャを読み込む
	numberSprite.resize(15);
	// パネルのテクスチャを読み込む
	for (int i = 0; i < numberSprite.size(); i++) {
		numberSprite[i].Initialize(Vector2(0.0f, 0.0f));
		numberSprite[i].SetNumber(i + 1);
	}
	blankSprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));

	ChangePanelData();

	BasePuzzle::Initialize();
}

void Puzzle15::Update() {
	mousePos = input_->GetMousePosition();
	DrawImGui();
}

void Puzzle15::Draw() {

}

void Puzzle15::SpriteDraw() {

}


void Puzzle15::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("puzzle15");
	ImGui::Text("puzzle15,UpDate,OK");
	ImGui::DragFloat2("mousePos", &mousePos.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}

void Puzzle15::ChangePanelData() {

}
