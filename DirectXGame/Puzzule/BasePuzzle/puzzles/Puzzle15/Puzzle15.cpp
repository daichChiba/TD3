#include "Puzzle15.h"
#include <random>

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

	blankSprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
	// CSVデータを再生成
	ReCreateCsvData();
	// パネルデータの変更
	ChangePanelData();

	BasePuzzle::Initialize();
}

void Puzzle15::Update() {
	mousePos = input_->GetMousePosition();
	DrawImGui();
}

void Puzzle15::Draw() {}

void Puzzle15::SpriteDraw() {}

void Puzzle15::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("puzzle15");
	ImGui::Text("puzzle15,UpDate,OK");
	ImGui::DragFloat2("mousePos", &mousePos.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}

void Puzzle15::ChangePanelData() {
	// CSVデータをPanelDataに変換
	panelData_.resize(csvData_.size());
	// NumberSpriteを初期化
	numberSprite.resize(15);
	for (int y = 0; y < panelData_.size(); y++) {
		panelData_[y].resize(csvData_[y].size());
		for (int x = 0; x < panelData_[y].size(); x++) {
#pragma region BlancPanelの生成
			if (csvData_[y][x] == 0) {
				panelData_[y][x].date = PanelType::Blank;
				Sprite* sprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f));
				Vector2 position = {static_cast<float>(x * panelSize_.x) + panelSize_.x * 0.5f, static_cast<float>(y * panelSize_.y) + panelSize_.y * 0.5f};
				sprite->SetPosition(position);
				panelData_[y][x].sprite = sprite;
			}
#pragma endregion
#pragma region Panel1
			if (csvData_[y][x] == 1) {
				panelData_[y][x].date = PanelType::Panle1;
				numberSprite[0].Initialize(Vector2(0.0f, 0.0f));
				numberSprite[0].SetNumber(1);
				Vector2 position = {static_cast<float>(x * panelSize_.x) + panelSize_.x * 0.5f, static_cast<float>(y * panelSize_.y) + panelSize_.y * 0.5f};
				numberSprite[0].SetPos(position);
				panelData_[y][x].sprite = &numberSprite[0].GetSprite(0);
			}
#pragma endregion
#pragma region Panel2
			if (csvData_[y][x] == 2) {
				panelData_[y][x].date = PanelType::Panle1;
				numberSprite[1].Initialize(Vector2(0.0f, 0.0f));
				numberSprite[1].SetNumber(2);
				Vector2 position = {static_cast<float>(x * panelSize_.x) + panelSize_.x * 0.5f, static_cast<float>(y * panelSize_.y) + panelSize_.y * 0.5f};
				numberSprite[1].SetPos(position);
				panelData_[y][x].sprite = &numberSprite[1].GetSprite(1);
			}
#pragma endregion
#pragma region Panel3
			if (csvData_[y][x] == 3) {
				panelData_[y][x].date = PanelType::Panle1;
				numberSprite[2].Initialize(Vector2(0.0f, 0.0f));
				numberSprite[2].SetNumber(3);
				Vector2 position = {static_cast<float>(x * panelSize_.x) + panelSize_.x * 0.5f, static_cast<float>(y * panelSize_.y) + panelSize_.y * 0.5f};
				numberSprite[2].SetPos(position);
				panelData_[y][x].sprite = &numberSprite[2].GetSprite(2);
			}
#pragma endregion
		}
	}
}

void Puzzle15::ReCreateCsvData() {
	csvData_.resize(4);
	// パネルの配置データを初期化し0~15までの数字をランダムに配置
	for (int y = 0; y < csvData_.size(); y++) {
		for (int x = 0; x < csvData_[y].size(); x++) {
			// 乱数生成
			csvData_[y][x] = rand() % 16;

			// 同じ数字がある場合は再度乱数を生成
			for (int i = 0; i < y; i++) {
				for (int j = 0; j < x; j++) {
					if (csvData_[y][x] == csvData_[i][j]) {
						csvData_[y][x] = rand() % 16;
					}
				}
			}
		}
	}
}
