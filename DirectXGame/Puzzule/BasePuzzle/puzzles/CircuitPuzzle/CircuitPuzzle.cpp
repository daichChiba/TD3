// CircuitPuzzle.cpp

#include "CircuitPuzzle.h"
#include "imgui.h"


// コンストラクタ
CircuitPuzzle::CircuitPuzzle() {}

// デストラクタ
CircuitPuzzle::~CircuitPuzzle() {
	if (fileAccessor_) {
		delete fileAccessor_;
		fileAccessor_ = nullptr;
	}
	// すべてのスプライトを解放
	for (auto sprite : panelSprites_) {
		delete sprite;
	}
	panelSprites_.clear();
}

// 初期化
void CircuitPuzzle::Initialize() {
	// FileAccessorの初期化
	fileAccessor_ = nullptr;
	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/CircuitPuzzle/CircuitPuzzle.json");

	// JSONからパネルサイズを読み込む
	panelSize_ = fileAccessor_->ReadVector3("Circuit", "size", Vector3());

	// JSONからisCompleteを読み込む
	isComplete_ = fileAccessor_->Read("Circuit", "isComplete", bool());
	time_ = fileAccessor_->Read("Circuit", "time", int());
	// JSONからCSVデータを読み込む
	csvData = fileAccessor_->ReadCsvData("Circuit", "panel");
	// パネルのテクスチャを読み込む
	panelTexture_ = TextureManager::Load("../Resources/CircuitPuzzle/panel.png");

	// CSVデータをPanelDataに変換
	panelData_.date.resize(csvData.size());
	// スプライト生成
	for (size_t i = 0; i < csvData.size(); ++i) {
		panelData_.date[i].resize(csvData[i].size());
		for (size_t j = 0; j < csvData[i].size(); ++j) {
			// CSVデータをPanelTypeに変換
			if (csvData[i][j] == 0) {
				// ブロックの場合
				panelData_.date[i][j] = PanelType::Block;
			} else if (csvData[i][j] == 1) {
				// パネルの場合
				panelData_.date[i][j] = PanelType::Panel;
				// スプライト生成
				Sprite* sprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
				// アンカーポイントを中心に設定
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f));

				// 初期位置
				float cellSize = 64.0f;
				// スプライトの位置を設定
				Vector2 position = {static_cast<float>(j * cellSize) + panelSize_.x * 0.5f, static_cast<float>(i * cellSize) + panelSize_.y * 0.5f};
				// スプライトの位置を設定
				sprite->SetPosition(position);
				// スプライトを追加
				panelSprites_.push_back(sprite);
				initialPositions.push_back(position); // 初期位置を保存
			} else if (csvData[i][j] == 2) {
				// パネルの場合
				panelData_.date[i][j] = PanelType::Panel2;
				// スプライト生成
				Sprite* sprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
				// アンカーポイントを中心に設定
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f));

				// 初期位置
				float cellSize = 64.0f;
				// スプライトの位置を設定
				Vector2 position = {static_cast<float>(j * cellSize) + panelSize_.x * 0.5f, static_cast<float>(i * cellSize) + panelSize_.y * 0.5f};
				// スプライトの位置を設定
				sprite->SetPosition(position);
				// スプライトを追加
				panelSprites_.push_back(sprite);
				initialPositions.push_back(position); // 初期位置を保存
			}
		}
	}

	BasePuzzle::Initialize();
}
// 更新
void CircuitPuzzle::Update() {
	// マウス座標を取得
	mousePos = input_->GetMousePosition();

	// マウスボタンが押された場合
	if (input_->IsPressMouse(0)) {
		// まだ選択されていない場合
		if (selectedSpriteIndex == -1) {
			int topMostSpriteIndex = -1; // 最も手前のスプライトのインデックス
			// 全てのパネルをチェック
			for (size_t i = 0; i < panelSprites_.size(); ++i) {
				// スプライトの位置を取得
				Vector2 spritePos = panelSprites_[i]->GetPosition();
				// スプライトのサイズを取得
				Vector2 spriteSize = {panelSize_.x, panelSize_.y};

				// マウス座標がスプライトの範囲内にあるかチェック
				if (mousePos.x >= spritePos.x - spriteSize.x / 2 && mousePos.x <= spritePos.x + spriteSize.x / 2) {
					if (mousePos.y >= spritePos.y - spriteSize.y / 2 && mousePos.y <= spritePos.y + spriteSize.y / 2) {
						// より手前にあるものを選択
						topMostSpriteIndex = static_cast<int>(i);
					}
				}
			}
			// 選択されたスプライトのインデックスを保存
			selectedSpriteIndex = topMostSpriteIndex;
		}
	}
	// マウスボタンが解放された場合
	else if (input_->IsReleseMouse(0)) {
		// ドロップ先を初期化
		int dropTargetIndex = -1;
		// スプライトが選択されている場合のみドロップ処理を行う
		if (selectedSpriteIndex != -1) {
			// スプライトの位置を取得
			Vector2 selectedSpritePos = panelSprites_[selectedSpriteIndex]->GetPosition();
			// 最も手前にあるドロップ先のインデックスを保存
			int topMostDropTargetIndex = -1;
			// ドロップ先のパネルを検索
			for (size_t i = 0; i < panelSprites_.size(); ++i) {
				// 自分自身は除く
				if (static_cast<int>(i) == selectedSpriteIndex)
					continue;
				// スプライトの位置を取得
				Vector2 spritePos = panelSprites_[i]->GetPosition();
				// スプライトのサイズを取得
				Vector2 spriteSize = {panelSize_.x, panelSize_.y};
				// マウス座標がスプライトの範囲内にあるかチェック
				if (mousePos.x >= spritePos.x - spriteSize.x / 2 && mousePos.x <= spritePos.x + spriteSize.x / 2) {
					if (mousePos.y >= spritePos.y - spriteSize.y / 2 && mousePos.y <= spritePos.y + spriteSize.y / 2) {
						// 最も手前にあるものをドロップ先とする
						topMostDropTargetIndex = static_cast<int>(i);
					}
				}
			}
			dropTargetIndex = topMostDropTargetIndex;

			// ドロップ先が見つかった場合、位置を交換
			if (dropTargetIndex != -1) {
				// スプライトの位置を入れ替え
				Vector2 selectedInitialPos = initialPositions[selectedSpriteIndex];
				Vector2 dropTargetInitialPos = initialPositions[dropTargetIndex];

				panelSprites_[selectedSpriteIndex]->SetPosition(dropTargetInitialPos);
				panelSprites_[dropTargetIndex]->SetPosition(selectedInitialPos);

				// スプライトのインデックスを入れ替え
				std::swap(panelSprites_[selectedSpriteIndex], panelSprites_[dropTargetIndex]);

				// インデックスも入れ替える
				std::swap(initialPositions[selectedSpriteIndex], initialPositions[dropTargetIndex]);

				// csvDataの内容をスプライトの位置に合わせて更新
				// まずcsvDataを更新
				csvData = fileAccessor_->ReadCsvData("Circuit", "panel");
				// csvDataを初期化
				for (size_t i = 0; i < csvData.size(); ++i) {
					for (size_t j = 0; j < csvData[i].size(); ++j) {
						csvData[i][j] = 0;
					}
				}
				// スプライトの位置からcsvDataのインデックスを計算
				for (size_t i = 0; i < panelSprites_.size(); ++i) {
					// スプライトの位置を取得
					Vector2 spritePos = panelSprites_[i]->GetPosition();
					// スプライトの位置からcsvDataのインデックスを計算
					int row = static_cast<int>((spritePos.y - panelSize_.y * 0.5f) / 64.0f);
					int col = static_cast<int>((spritePos.x - panelSize_.x * 0.5f) / 64.0f);
					// csvDataの値を更新
					if (panelSprites_[i]) {
						if (panelData_.date[row][col] == PanelType::Panel) {
							csvData[row][col] = 1;
						} else if (panelData_.date[row][col] == PanelType::Panel2) {
							csvData[row][col] = 2;
						}
					}
				}

				// csvDataを保存
				fileAccessor_->WriteCsvData("Circuit", "panel", csvData);
			}
		}
		// 選択を解除
		selectedSpriteIndex = -1;
	}

	// スプライトが選択されている場合、位置を更新
	if (selectedSpriteIndex != -1) {
		// スプライトの位置をマウス座標に設定
		panelSprites_[selectedSpriteIndex]->SetPosition(mousePos);
		// アンカーポイントを中心に設定
		panelSprites_[selectedSpriteIndex]->SetAnchorPoint(Vector2(0.5f, 0.5f));
	}
	DrawImGui();
}
void CircuitPuzzle::Draw() {}

// Sprite描画
void CircuitPuzzle::SpriteDraw() {
	// CSVデータに基づいて画像を描画
	for (size_t i = 0; i < panelSprites_.size(); ++i) {

		// panelSprites_[i]->SetPosition(Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
		panelSprites_[i]->Draw();
	}
}
// ImGui描画
void CircuitPuzzle::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("CircuitPuzzle");
	ImGui::Text("CircuitPuzzle,UpDate,OK");
	ImGui::DragFloat2("mousePos", &mousePos.x, 0.1f);
	ImGui::DragInt("selectedSpriteIndex", &selectedSpriteIndex, 1);
	// Vector3の値をImGuiで編集
	float panelSizeArray[3] = {panelSize_.x, panelSize_.y, panelSize_.z};
	if (ImGui::DragFloat3("PanelSize", panelSizeArray, 0.1f)) { // 値が変更されたら
		panelSize_.x = panelSizeArray[0];
		panelSize_.y = panelSizeArray[1];
		panelSize_.z = panelSizeArray[2];
		fileAccessor_->WriteVector3("Circuit", "Pos", panelSize_); // Vector3を書き込む
	}
	// ImGuiでチェックボックスを表示して値を編集
	if (ImGui::Checkbox("isComplete", &isComplete_)) {              // 値が変更されたら
		fileAccessor_->Write("Circuit", "isComplete", isComplete_); // bool値を書き込む
	}
	ImGui::DragInt("time", &time_, 1);              // int値をImGuiで編集
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
				const char* panelTypeStr = {"-"};
				// テキストを表示
				ImGui::Text(panelTypeStr);
				if (row[column] == PanelType::Block) {
					panelTypeStr = "Block";
				} else if (row[column] == PanelType::Panel) {
					panelTypeStr = "Panel";
				} else if (row[column] == PanelType::Panel2) {
					panelTypeStr = "Panel2";
				}
				// テキストを表示
				ImGui::Text(panelTypeStr);
			}
		}
		ImGui::EndTable();
		// それぞれのパネルがどこにいるかを表示
		for (size_t i = 0; i < panelSprites_.size(); ++i) {
			ImGui::Text("Panel %d: (%.1f, %.1f)", i, panelSprites_[i]->GetPosition().x, panelSprites_[i]->GetPosition().y);
		}
		// それぞれのパネルの大きさを表示
		for (size_t i = 0; i < panelSprites_.size(); ++i) {
			ImGui::Text("Panel %d: (%.1f, %.1f)", i, panelSprites_[i]->GetSize().x, panelSprites_[i]->GetSize().y);
		}
	}
	fileAccessor_->Save(); // JSONファイルを保存
	ImGui::End();
#endif
}

void CircuitPuzzle::UpdatePanelData() {
	// CSVデータとPanelDataを初期化
	csvData.clear();
	panelData_.date.clear();
	panelSprites_.clear();

	// JSONからCSVデータを読み込む
	csvData = fileAccessor_->ReadCsvData("Circuit", "panel");

	// CSVデータをPanelDataに変換
	panelData_.date.resize(csvData.size());
	// スプライト生成
	for (size_t i = 0; i < csvData.size(); ++i) {
		panelData_.date[i].resize(csvData[i].size());
		for (size_t j = 0; j < csvData[i].size(); ++j) {
			// CSVデータをPanelTypeに変換
			if (csvData[i][j] == 0) {
				// ブロックの場合
				panelData_.date[i][j] = PanelType::Block;
			} else if (csvData[i][j] == 1) {
				// パネルの場合
				panelData_.date[i][j] = PanelType::Panel;
				// スプライト生成
				Sprite* sprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
				// アンカーポイントを中心に設定
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f));

				// スプライトの位置を設定 (CSVデータから計算)
				float cellSize = 64.0f;
				Vector2 position = {static_cast<float>(j * cellSize) + panelSize_.x * 0.5f, static_cast<float>(i * cellSize) + panelSize_.y * 0.5f};
				sprite->SetPosition(position);
				// スプライトを追加
				panelSprites_.push_back(sprite);
			} else if (csvData[i][j] == 2) {
				// パネル2の場合
				panelData_.date[i][j] = PanelType::Panel2;
				// スプライト生成
				Sprite* sprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
				// アンカーポイントを中心に設定
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f));

				// スプライトの位置を設定 (CSVデータから計算)
				float cellSize = 64.0f;
				Vector2 position = {static_cast<float>(j * cellSize) + panelSize_.x * 0.5f, static_cast<float>(i * cellSize) + panelSize_.y * 0.5f};
				sprite->SetPosition(position);
				// スプライトを追加
				panelSprites_.push_back(sprite);
			}
		}
	}
}