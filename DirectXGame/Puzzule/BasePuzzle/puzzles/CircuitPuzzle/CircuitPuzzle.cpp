#include "CircuitPuzzle.h" // CircuitPuzzle.hをインクルード

// コンストラクタ
CircuitPuzzle::CircuitPuzzle(){}

// デストラクタ
CircuitPuzzle::~CircuitPuzzle() {
	if (fileAccessor_) {
		delete fileAccessor_;
		fileAccessor_ = nullptr;
	}
	// panelSprite_ は1つなので、ここで解放
	// すべてのスプライトを解放
	for (auto sprite : panelSprites_) {
		delete sprite;
	}
	panelSprites_.clear();
}

// 初期化
void CircuitPuzzle::Initialize() {
	fileAccessor_ = nullptr;
	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/CircuitPuzzle/CircuitPuzzle.json");

	// JSONからパネルサイズを読み込む
	panelSize_ = fileAccessor_->ReadVector3("Circuit", "Pos", Vector3());

	// JSONからisCompleteを読み込む
	isComplete_ = fileAccessor_->Read("Circuit", "isComplete", bool());
	time_ = fileAccessor_->Read("Circuit", "time", int());
	// JSONからCSVデータを読み込む
	std::vector<std::vector<int>> csvData = fileAccessor_->ReadCsvData("Circuit", "panel.csv");
	panelTexture_ = TextureManager::Load("../Resources/CircuitPuzzle/panel.png");                    // block.png ではなく panel.png をロード

	// CSVデータをPanelDataに変換
	panelData_.date.resize(csvData.size());
	for (size_t i = 0; i < csvData.size(); ++i) {
		panelData_.date[i].resize(csvData[i].size());
		for (size_t j = 0; j < csvData[i].size(); ++j) {
			// CSVデータをPanelTypeに変換
			if (csvData[i][j] == 0) {
				panelData_.date[i][j] = PanelType::Block;
			} else {
				panelData_.date[i][j] = PanelType::Panel;
				Sprite* sprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x, panelSize_.y));
				panelSprites_.push_back(sprite);
			}
		}
	}
	BasePuzzle::Initialize();
}
// 更新
void CircuitPuzzle::Update() {
	mousePos = input_->GetMousePosition();
	DrawImGui();
}

// 描画
void CircuitPuzzle::Draw() {

}


void CircuitPuzzle::SpriteDraw() {
	// CSVデータに基づいて画像を描画
	int cellSize = 64;
	// スプライトのインデックス
	size_t spriteIndex = 0;
	// パネルの描画
	for (int y = 0; y < panelData_.date.size(); ++y) {
		for (int x = 0; x < panelData_.date[y].size(); ++x) {
			// パネルの種類がパネルの場合
			if (panelData_.date[y][x] == PanelType::Panel) {
				// スプライトを描画
				Vector2 position = {static_cast<float>(x * 1.5f * cellSize), static_cast<float>(y * 1.5f * cellSize)};
				panelSprites_[spriteIndex]->SetPosition(position);
				panelSprites_[spriteIndex]->Draw();
				++spriteIndex;
			}
		}
	}
}

// ImGui描画
void CircuitPuzzle::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("CircuitPuzzle");
	ImGui::Text("CircuitPuzzle,UpDate,OK");
	ImGui::DragFloat2("mousePos", &mousePos.x, 0.1f);
	// Vector3の値をImGuiで編集
	float panelSizeArray[3] = {panelSize_.x, panelSize_.y, panelSize_.z};
	if (ImGui::DragFloat3("PanelSize", panelSizeArray, 0.1f)) { // 値が変更されたら
		panelSize_.x = panelSizeArray[0];
		panelSize_.y = panelSizeArray[1];
		panelSize_.z = panelSizeArray[2];
		fileAccessor_->WriteVector3("Circuit", "Pos", panelSize_); // Vector3を書き込む
	}
	// ImGuiでチェックボックスを表示して値を編集
	if (ImGui::Checkbox("isComplete", &isComplete_)) {             // 値が変更されたら
		fileAccessor_->Write("Circuit", "isComplete", isComplete_); // bool値を書き込む
	}
	ImGui::DragInt("time", &time_, 1); // int値をImGuiで編集
	fileAccessor_->Write("Circuit", "time", time_); // int値を書き込む

    // PanelDataをImGuiテーブルとして表示
	if (ImGui::BeginTable("PanelData", panelData_.date.empty() ? 1 : static_cast<int>(panelData_.date[0].size()))) {
		// ヘッダー
		// テーブルの列を設定
		for (int column = 0; column < (panelData_.date.empty() ? 1 : static_cast<int>(panelData_.date[0].size())); ++column) {
			// 列の設定
			ImGui::TableSetupColumn(("Column " + std::to_string(column)).c_str());
		}
		// ヘッダー行
		ImGui::TableHeadersRow();

		// データ
		for (const auto& row : panelData_.date) {
			// 次の行に移動
			ImGui::TableNextRow();
			// 各列にデータを表示
			for (int column = 0; column < row.size(); ++column) {
				// 列のインデックスを設定
				ImGui::TableSetColumnIndex(column);
				// パネルの種類を文字列に変換して表示
				const char* panelTypeStr = (row[column] == PanelType::Block) ? "Block" : "Panel";
				// テキストを表示
				ImGui::Text(panelTypeStr);
			}
		}
		ImGui::EndTable();
	}
	fileAccessor_->Save(); // JSONファイルを保存
	ImGui::End();
#endif
}