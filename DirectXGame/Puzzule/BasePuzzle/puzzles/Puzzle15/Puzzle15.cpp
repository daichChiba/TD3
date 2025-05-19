#include "Puzzle15.h"

using namespace KamataEngine;

Puzzle15::Puzzle15() {}

Puzzle15::~Puzzle15() {}

void Puzzle15::Initialize() {

	// 中心座標を設定
	centor_ = {500.0f, 200.0f};

	// 乱数生成器を初期化
	std::random_device rd;
	randomSeed.seed(rd());
	std::uniform_real_distribution<float> randomFloat(-1.0f, 1.0f);

	// パネルのテクスチャをロード
	panelTextures_.push_back(TextureManager::Load("Puzzle15/panel.png"));
	for (int i = 1; i <= 15; i++) {
		panelTextures_.push_back(TextureManager::Load("Puzzle15/puzzle15_" + std::to_string(i) + ".png"));
	}

	// パネルデータの初期化
	for (size_t i = 0; i < 16; i++) {
		PanelDate panelData;
		panelData.date = static_cast<PanelType>(i);
		// パネルの初期位置をランダムに設定
		panelData.pos = {randomFloat(randomSeed) * centor_.x + 640.0f, randomFloat(randomSeed) * centor_.y + 320.0f};
		panelData.prePos = panelData.pos; // 初期位置を保存

		// パネルのスプライトを作成
		Sprite* panelDate = Sprite::Create(panelTextures_[i], panelData.pos);
		panelDate->SetAnchorPoint(Vector2(0.5f, 0.5f));
		panelData.sprite = panelDate;
		panelData_.push_back(panelData);
	}

	// 黒のテクスチャをロード
	BlaccTexture_ = TextureManager::Load("Black1x1.png");

	// JSONファイルの初期化
	fileAccessor_ = nullptr;
	fileAccessor_ = new FileJson::FileAccessor("Resources/Puzzle15/Panel15.json");

	// JSONファイルからデータを読み込む
	panelSize_ = fileAccessor_->ReadVector3("Puzzle15", "size", Vector3());
	isClear_ = fileAccessor_->Read("Puzzle15", "isClear", bool());
	csvData_ = fileAccessor_->ReadCsvData("Puzzle15", "startPanel");
	clearData = fileAccessor_->ReadCsvData("Puzzle15", "clearPanel");

	// パネルの初期位置をCSVデータから設定
	for (size_t row = 0; row < csvData_.size(); row++) {
		for (size_t col = 0; col < csvData_[row].size(); col++) {
			// Csvの値が16の場合のみ、黒いパネルを生成
			if (csvData_[row][col] == 16) {
				// パネルの座標を計算
				Vector2 panelPos;
				panelPos.x = static_cast<float>(col) * panelSize_.x + centor_.x + panelSize_.x * 0.5f * static_cast<float>(col);
				panelPos.y = static_cast<float>(row) * panelSize_.y + centor_.y + panelSize_.y * 0.5f * static_cast<float>(row);
				// パネルのスプライトを作成
				Sprite* BlackPanel = Sprite::Create(BlaccTexture_, panelPos);
				BlackPanel->SetAnchorPoint(Vector2(0.5f, 0.5f));
				BlackPanel->SetSize({panelSize_.x, panelSize_.y});

				// 生成した黒いパネルのスプライトをリストに追加
				BlackPanels.push_back({BlackPanel, false});
			}
		}
	}

	BasePuzzle::Initialize();
}

void Puzzle15::Update() {
	// マウスの座標を取得
	mousePos = input_->GetMousePosition();

	// パネルがホールドされていない場合
	if (!isHold_) {
		// マウスがクリックされた場合
		if (input_->IsTriggerMouse(0)) {
			int topMostPanelIndex = -1; // 最も手前にあるパネルのインデックス

			// 全てのパネルに対して当たり判定
			for (int i = 0; i < panelData_.size(); i++) {
				// パネルの範囲内にマウスがあるか判定
				if (mousePos.x >= panelData_[i].pos.x - panelData_[i].sprite->GetSize().x / 2 && mousePos.x <= panelData_[i].pos.x + panelData_[i].sprite->GetSize().x / 2 &&
				    mousePos.y >= panelData_[i].pos.y - panelData_[i].sprite->GetSize().y / 2 && mousePos.y <= panelData_[i].pos.y + panelData_[i].sprite->GetSize().y / 2) {

					topMostPanelIndex = i; // 最後に検出されたパネルを記録（＝最も手前）
					if (panelData_[i].blackPanelIndex != -1) {
						BlackPanels[panelData_[i].blackPanelIndex].isLock = false; // 黒いパネルのロックを解除
						// 前の黒いパネルのインデックスを保存
						panelData_[i].preBlackPanelIndex = panelData_[i].blackPanelIndex;
						panelData_[i].blackPanelIndex = -1; // パネルのインデックスをリセット
					}
				}
			}

			// いずれかのパネルがクリックされた場合
			if (topMostPanelIndex != -1) {
				holdPos_ = mousePos;
				isHold_ = true;
				HoldIndex = topMostPanelIndex; // 選択されたパネルのインデックスを記録
			}
		}
	}
	// パネルがホールドされている場合
	else {
		// マウスが押されている場合
		if (input_->IsPressMouse(0)) {
			// 選択されたパネルのみをマウスに合わせて移動
			panelData_[HoldIndex].sprite->SetPosition(mousePos);
			panelData_[HoldIndex].pos = mousePos;
		}
		// マウスが離された場合
		if (input_->IsReleseMouse(0)) {
			isHold_ = false;
			// パネルデータの更新処理
			BlackPanelOnCorision();
		}
	}

	DrawImGui();
}

void Puzzle15::Draw() {}

void Puzzle15::SpriteDraw() {
	// 全ての白いパネルを描画
	for (BlackPanelDate whitePanel : BlackPanels) {
		whitePanel.sprite->Draw();
	}

	// 全てのパネルを描画
	for (size_t i = 0; i < panelData_.size(); i++) {
		panelData_[i].sprite->Draw();
	}
}

void Puzzle15::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("puzzle15");
	ImGui::Text("puzzle15,UpDate,OK");
	if (isClear_) {
		ImGui::Text("isClear : true");
	} else {
		ImGui::Text("isClear : false");
	}
	ImGui::DragFloat2("mousePos", &mousePos.x, 0.1f);
	ImGui::Text("selectedPanelIndex_ : %d", HoldIndex); // 選択されているパネルのインデックスをデバッグ表示
	for (size_t row = 0; row < csvData_.size(); row++) {
		for (size_t col = 0; col < csvData_[row].size(); col++) {
			ImGui::Text("csvData[%d][%d] : %d", row, col, csvData_[row][col]);
		}
	}

	ImGui::End();
#endif // _DEBUG
}

// パネルデータの更新
void Puzzle15::BlackPanelOnCorision() {
	if (HoldIndex != -1) {
		Vector2 currentPos = panelData_[HoldIndex].pos;

		// 黒いパネルの場所にあるかを確認
		Sprite* targetBlackPanel_ = nullptr;
		int i = IsInsideBlackPanel(currentPos, targetBlackPanel_);
		if (i != -1) {
			if (!BlackPanels[i].isLock) {
				// ロックして位置を固定
				panelData_[HoldIndex].pos = targetBlackPanel_->GetPosition(); // 正しい位置に固定
				panelData_[HoldIndex].sprite->SetPosition(targetBlackPanel_->GetPosition());
				IsClear(i); // パズルが完成したかどうかを判定

				// 黒いパネルのロック状態を更新
				BlackPanels[i].isLock = true;
				panelData_[HoldIndex].blackPanelIndex = i;                // 黒いパネルのインデックスを保存
				panelData_[HoldIndex].prePos = panelData_[HoldIndex].pos; // 初期位置を更新
			} else {
				if (panelData_[HoldIndex].preBlackPanelIndex != -1) {
					// 前の黒いパネルのロックを解除
					BlackPanels[panelData_[HoldIndex].preBlackPanelIndex].isLock = true;
					// 前の黒いパネルのインデックスをリセット
					panelData_[HoldIndex].blackPanelIndex = panelData_[HoldIndex].preBlackPanelIndex;
					panelData_[HoldIndex].preBlackPanelIndex = -1;
				}
				// 黒いパネルがロックされている場合は元の位置に戻す
				panelData_[HoldIndex].pos = panelData_[HoldIndex].prePos;
				panelData_[HoldIndex].sprite->SetPosition(panelData_[HoldIndex].prePos);
			}
		} else {
			// 黒いパネルの位置にない場合は元の位置に戻す
			panelData_[HoldIndex].pos = mousePos;
			panelData_[HoldIndex].sprite->SetPosition(mousePos);
			panelData_[HoldIndex].prePos = mousePos; // 初期位置を更新
			panelData_[HoldIndex].blackPanelIndex = -1;
			panelData_[HoldIndex].preBlackPanelIndex = -1;
		}
		HoldIndex = -1; // 選択されたパネルのインデックスをリセット
	}
}

// 黒いパネルがあるかどうかを判定する関数
int Puzzle15::IsInsideBlackPanel(Vector2 pos, Sprite*& targetBlackPanel) {
	int i = 0;
	for (BlackPanelDate blackPanel : BlackPanels) {
		Vector2 blackPanelPos = blackPanel.sprite->GetPosition();
		Vector2 blackPanelSize = blackPanel.sprite->GetSize();

		if (pos.x >= blackPanelPos.x - blackPanelSize.x / 2 && pos.x <= blackPanelPos.x + blackPanelSize.x / 2 && pos.y >= blackPanelPos.y - blackPanelSize.y / 2 &&pos.y <= blackPanelPos.y + blackPanelSize.y / 2) {
			targetBlackPanel = blackPanel.sprite; // 黒いパネルを取得
			return i;
		}
		i++;
	}
	return -1;
}

void Puzzle15::IsClear(int blackPanelIndex) {
	int x = blackPanelIndex % 4; // 黒いパネルのX座標
	int y = blackPanelIndex / 4; // 黒いパネルのY座標
	csvData_[y][x] = static_cast<int>(panelData_[HoldIndex].date); // CSVデータにパネルの種類を保存
	// パズルが完成したかどうかを判定
	for (size_t row = 0; row < csvData_.size(); row++) {
		for (size_t col = 0; col < csvData_[row].size(); col++) {
			if (csvData_[row][col] != clearData[row][col]) {
				isClear_=false; // パズルが完成していない
				return;
			}
		}
	}
	isClear_=true; // パズルが完成している

	fileAccessor_->Write("Puzzle15", "isClear", isClear_); // JSONファイルに書き込み
	fileAccessor_->Save();                                 // JSONファイルを保存
}
