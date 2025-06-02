// CircuitPuzzle.cpp

#include "CircuitPuzzle.h"
#include "imgui.h"

// コンストラクタ
CircuitPuzzle::CircuitPuzzle() {}

// デストラクタ
CircuitPuzzle::~CircuitPuzzle() {
	// FileAccessorの解放
	if (fileAccessor_) {
		delete fileAccessor_;
		fileAccessor_ = nullptr;
	}
}

// 初期化
void CircuitPuzzle::Initialize() {
	// random_deviceを使用してシードを生成
	std::random_device rd;
	// 乱数生成器を初期化
	randomSeed.seed(rd());
	// 乱数生成器の初期化
	std::uniform_int_distribution<int> random(1, 6);
	// 乱数を生成
	int randomNum = 2;

	// FileAccessorの初期化
	fileAccessor_ = nullptr;
	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/CircuitPuzzle/CircuitPuzzle.json");

	// JSONからパネルサイズを読み込む
	panelSize_ = fileAccessor_->ReadVector3("Circuit", "size", Vector3());

	// JSONからisCompleteを読み込む
	isClear_ = fileAccessor_->Read("Circuit", "isClear", bool());
	time_ = fileAccessor_->Read("Circuit", "time", int());
	// JSONからCSVデータを読み込む
	csvData_ = fileAccessor_->ReadCsvData("Circuit", "stage_" + std::to_string(randomNum));
	answerData_ = fileAccessor_->ReadCsvData("Circuit", "answer_" + std::to_string(randomNum));
	// パネルのテクスチャを読み込む
	panelTexture_ = TextureManager::Load("../Resources/CircuitPuzzle/panel.png");
	for (int i = 1; i <= 24; i++) {
		panelTextures_.push_back(TextureManager::Load("../Resources/CircuitPuzzle/CircuitPuzzles/circuitPuzzle_" + std::to_string(i) + ".png"));
		connectedPanelTextures_.push_back(TextureManager::Load("../Resources/CircuitPuzzle/correctPanel/correctPanel_" + std::to_string(i) + ".png"));
	}
	centor_ = {500.0f, 200.0f};

	ChangePanelData();

	BasePuzzle::Initialize();
}
// 更新
void CircuitPuzzle::Update() {
	// マウス座標を取得
	mousePos = input_->GetMousePosition();

	// パネルデータの更新
	for (size_t y = 0; y < panelData_.size(); y++) {
		for (size_t x = 0; x < panelData_[y].size(); x++) {
			// パネルが空白でない場合
			if (panelData_[y][x].date != PanelType::Blank) {
				// パネルの座標を更新
				panelData_[y][x].sprite->SetPosition({static_cast<float>(x * panelSize_.x + panelSize_.x * 0.5f + centor_.x), static_cast<float>(y * panelSize_.y + panelSize_.y * 0.5f + centor_.y)});
			}
		}
	}

	if (!isHold_) {
		// マウスの左ボタンが押された場合
		if (input_->IsTriggerMouse(0)) {
			for (size_t y = 0; y < panelData_.size(); y++) {
				for (size_t x = 0; x < panelData_[y].size(); x++) {
					// スプライトの位置を取得
					Vector2 spritePos = panelData_[y][x].sprite->GetPosition();
					// スプライトのサイズを取得
					Vector2 spriteSize = {panelSize_.x, panelSize_.y};
					// マウス座標がスプライトの範囲内にあるかチェック
					if (mousePos.x >= spritePos.x - spriteSize.x / 2 && mousePos.x <= spritePos.x + spriteSize.x / 2) {
						if (mousePos.y >= spritePos.y - spriteSize.y / 2 && mousePos.y <= spritePos.y + spriteSize.y / 2) {
							// 動かせないパネルの場合はスキップ
							if (panelData_[y][x].date == PanelType::StartPanel || panelData_[y][x].date == PanelType::GoalPanel || panelData_[y][x].date == PanelType::Blank ||
							    panelData_[y][x].date == PanelType::LockTPanel || panelData_[y][x].date == PanelType::LockLPanel || panelData_[y][x].date == PanelType::LockInvertedL ||
							    panelData_[y][x].date == PanelType::LockIPanel || panelData_[y][x].date == PanelType::LockUpReverseLPanel || panelData_[y][x].date == PanelType::LockUpInvertedLPanel ||
							    panelData_[y][x].date == PanelType::LockUpReverseTPanel || panelData_[y][x].date == PanelType::LockPlusPanel ||
							    panelData_[y][x].date == PanelType::LockLeftRotateTPanel || panelData_[y][x].date == PanelType::LockRiteRotateTPanel ||
							    panelData_[y][x].date == PanelType::LockMinusPanel) {
								continue;
							}

							// 選択されたスプライトのインデックスを保存
							holdPos_ = IntVector2(static_cast<int>(x), static_cast<int>(y));
							isHold_ = true;
						}
					}
				}
			}
		}
	} else {
		// マウスの左ボタンが押されている場合
		if (input_->IsPressMouse(0)) {
			// ドラッグ中のスプライトの位置を更新
			panelData_[holdPos_.y][holdPos_.x].sprite->SetPosition(mousePos);
		}
		// マウスの左ボタンが離された場合
		if (input_->IsReleseMouse(0)) {
			UpdatePanelData();
		}
	}
	fileAccessor_->Save();
	CheckClear();
	CorrectPanel();
	DrawImGui();
}
void CircuitPuzzle::Draw() {}

// Sprite描画
void CircuitPuzzle::SpriteDraw() {
	// CSVデータに基づいて画像を描画
	for (size_t y = 0; y < panelData_.size(); y++) {
		for (size_t x = 0; x < panelData_[y].size(); x++) {
			// if (panelData_[y][x].date != PanelType::Blank) {
			//  スプライト描画
			panelData_[y][x].sprite->Draw();
			//}
		}
	}
}
void CircuitPuzzle::CheckClear() {
	ConnectedPanel(); // 接続状態を更新
	bool isGoalCorrect = false;
	for (const auto& row : panelData_) {
		for (const auto& panel : row) {
			if (panel.date == PanelType::GoalPanel && panel.isCorrect) {
				isGoalCorrect = true;
				break;
			}
		}
		if (isGoalCorrect)
			break;
	}
	isClear_ = isGoalCorrect;
	fileAccessor_->Write("Circuit", "isClear", isClear_);
	fileAccessor_->Save();
}
void CircuitPuzzle::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("CircuitPuzzle");
	ImGui::Checkbox("isClear", &isClear_);
	if (isClear_) {
		ImGui::Text("Clear!!");
	} else {
		ImGui::Text("Not Clear");
	}

	// Panelデータを表示
	for (size_t y = 0; y < panelData_.size(); y++) {
		for (size_t x = 0; x < panelData_[y].size(); x++) {
			ImGui::Text("Panel[%d][%d]: %d", static_cast<int>(y), static_cast<int>(x), static_cast<int>(panelData_[y][x].date));
			if (panelData_[y][x].isCorrect) {
				ImGui::Text("Correct!!");
			} else {
				ImGui::Text("Not Correct");
			}
		}
	}

	ImGui::End();
#endif
}

void CircuitPuzzle::ChangePanelData() {
	// CSVデータをPanelDataに変換
	panelData_.resize(csvData_.size());
	// スプライト生成
	for (size_t i = 0; i < csvData_.size(); ++i) {
		panelData_[i].resize(csvData_[i].size());
		for (size_t j = 0; j < csvData_[i].size(); ++j) {
			// CSVデータをPanelTypeに変換
			if (csvData_[i][j] == 0) {
				// ブロックの場合
				panelData_[i][j].date = PanelType::Blank;
				Sprite* sprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f));
				Vector2 position = {static_cast<float>(j * panelSize_.x) + panelSize_.x * 0.5f + centor_.x, static_cast<float>(i * panelSize_.y) + panelSize_.y * 0.5f + centor_.y};
				sprite->SetPosition(position);
				panelData_[i][j].sprite = sprite;
			} else {
				panelData_[i][j].date = static_cast<PanelType>(csvData_[i][j]);
				Sprite* sprite = Sprite::Create(panelTextures_[csvData_[i][j] - 1], Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f));
				Vector2 position = {static_cast<float>(j * panelSize_.x) + panelSize_.x * 0.5f + centor_.x, static_cast<float>(i * panelSize_.y) + panelSize_.y * 0.5f + centor_.y};
				sprite->SetPosition(position);
				panelData_[i][j].sprite = sprite;
				if (panelData_[i][j].date == PanelType::StartPanel) {
					panelData_[i][j].isCorrect = true;
				}
			}
		}
	}
}

void CircuitPuzzle::UpdatePanelData() {
	for (size_t y = 0; y < panelData_.size(); y++) {
		for (size_t x = 0; x < panelData_[y].size(); x++) {
			// スプライトの位置を取得
			Vector2 spritePos = panelData_[y][x].sprite->GetPosition();
			// スプライトのサイズを取得
			Vector2 spriteSize = {panelSize_.x, panelSize_.y};
			bool dropTargetIsFixed =
			    (panelData_[y][x].date == PanelType::StartPanel || panelData_[y][x].date == PanelType::GoalPanel || panelData_[y][x].date == PanelType::Blank ||
			     panelData_[y][x].date == PanelType::LockTPanel || panelData_[y][x].date == PanelType::LockLPanel || panelData_[y][x].date == PanelType::LockInvertedL ||
			     panelData_[y][x].date == PanelType::LockIPanel || panelData_[y][x].date == PanelType::LockUpReverseLPanel || panelData_[y][x].date == PanelType::LockUpInvertedLPanel ||
			     panelData_[y][x].date == PanelType::LockUpReverseTPanel || panelData_[y][x].date == PanelType::LockPlusPanel || panelData_[y][x].date == PanelType::LockLeftRotateTPanel ||
			     panelData_[y][x].date == PanelType::LockRiteRotateTPanel || panelData_[y][x].date == PanelType::LockMinusPanel);

			// マウス座標がスプライトの範囲内にあるかチェック
			if (mousePos.x >= spritePos.x - spriteSize.x / 2 && mousePos.x <= spritePos.x + spriteSize.x / 2) {
				if (mousePos.y >= spritePos.y - spriteSize.y / 2 && mousePos.y <= spritePos.y + spriteSize.y / 2) {
					if (!dropTargetIsFixed) {
						if (panelData_[y][x].date != panelData_[holdPos_.y][holdPos_.x].date) {
							// パネルの交換
							PanelType temp = panelData_[holdPos_.y][holdPos_.x].date;
							panelData_[holdPos_.y][holdPos_.x].date = panelData_[y][x].date;
							panelData_[y][x].date = temp;
							// スプライトの交換
							Sprite* tempSprite = panelData_[holdPos_.y][holdPos_.x].sprite;
							panelData_[holdPos_.y][holdPos_.x].sprite = panelData_[y][x].sprite;
							panelData_[y][x].sprite = tempSprite;
							// csvDataの入れ替え
							int tempData = csvData_[holdPos_.y][holdPos_.x];
							csvData_[holdPos_.y][holdPos_.x] = csvData_[y][x];
							csvData_[y][x] = tempData;
							// jsonファイルに書き込む
							fileAccessor_->WriteCsvData("Circuit", "panel", csvData_);
						}
					}
				}
			}
		}
	}

	isHold_ = false;
}

void CircuitPuzzle::CorrectPanel() {
	ConnectedPanel();

	// startパネルの一個下のパネルが正しいがどうか
	for (size_t y = 0; y < panelData_.size(); y++) {
		for (size_t x = 0; x < panelData_[y].size(); x++) {
			if (panelData_[y][x].isCorrect) {
				if (panelData_[y][x].date != PanelType::Blank) {
					panelData_[y][x].sprite->SetTextureHandle(connectedPanelTextures_[static_cast<int>(panelData_[y][x].date) - 1]);
				}
			} else {
				if (panelData_[y][x].date != PanelType::Blank) {
					panelData_[y][x].sprite->SetTextureHandle(panelTextures_[static_cast<int>(panelData_[y][x].date) - 1]);
				}
			}
		}
	}
}

void CircuitPuzzle::ConnectedPanel() {
	// 全てのパネルのisCorrectを一旦falseにする (スタートパネルを除く)
	for (size_t y = 0; y < panelData_.size(); ++y) {
		for (size_t x = 0; x < panelData_[y].size(); ++x) {
			if (panelData_[y][x].date != PanelType::StartPanel) {
				panelData_[y][x].isCorrect = false;
			} else {
				panelData_[y][x].isCorrect = true; // スタートパネルは常に正しい
			}
		}
	}

	bool changed = true;
	while (changed) {
		changed = false;
		for (size_t y = 0; y < panelData_.size(); ++y) {
			for (size_t x = 0; x < panelData_[y].size(); ++x) {
				if (panelData_[y][x].isCorrect && panelData_[y][x].date != PanelType::Blank) {
					PanelType currentPanelType = panelData_[y][x].date;
					// 現在のパネルの出力方向を取得 (panelConnectionsを使用)
					auto it = panelConnections.find(currentPanelType);
					if (it != panelConnections.end()) {
						for (Direction outputDir : it->second) {
							int nextX = static_cast<int>(x);
							int nextY = static_cast<int>(y);
							Direction inputDir = Direction::None; // 入力方向を初期化

							// 出力方向に応じて隣接パネルの座標と期待される入力方向を計算
							if (outputDir == Direction::Up) {
								nextY--;
								inputDir = Direction::Down;
							} else if (outputDir == Direction::Down) {
								nextY++;
								inputDir = Direction::Up;
							} else if (outputDir == Direction::Left) {
								nextX--;
								inputDir = Direction::Right;
							} else if (outputDir == Direction::Right) {
								nextX++;
								inputDir = Direction::Left;
							}

							// 隣接パネルが範囲内にあるか確認
							if (nextY >= 0 && nextY < panelData_.size() && nextX >= 0 && nextX < panelData_[nextY].size()) {
								if (panelData_[nextY][nextX].date != PanelType::Blank && !panelData_[nextY][nextX].isCorrect) {
									// 隣接パネルの入力方向を取得
									auto nextPanelIt = panelConnections.find(panelData_[nextY][nextX].date);
									if (nextPanelIt != panelConnections.end()) {
										for (Direction nextInputDir : nextPanelIt->second) {
											// 隣接パネルが期待される入力方向を持っているか確認
											if (nextInputDir == inputDir) {
												panelData_[nextY][nextX].isCorrect = true;
												changed = true;
												break; // 一致する入力方向が見つかったら終了
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// ゴールパネルが正しく接続されているか最終確認
	bool goalFound = false;
	for (size_t y = 0; y < panelData_.size(); ++y) {
		for (size_t x = 0; x < panelData_[y].size(); ++x) {
			if (panelData_[y][x].date == PanelType::GoalPanel && panelData_[y][x].isCorrect) {
				goalFound = true;
				break;
			}
		}
		if (goalFound)
			break;
	}

	if (!goalFound) {
		// ゴールに正しく接続されていない場合、クリアフラグを下げるなどの処理
		isClear_ = false;
	}
}