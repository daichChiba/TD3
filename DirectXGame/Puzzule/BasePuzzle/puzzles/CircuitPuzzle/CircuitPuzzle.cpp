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
	int randomNum = random(randomSeed);

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
	BackgroundTexture_ = TextureManager::Load("../Resources/CircuitPuzzle/brick.png");
	backgroundSprite_ = Sprite::Create(BackgroundTexture_, Vector2(1000.0f, 400.0f));
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
	backgroundSprite_->SetPosition(Vector2(0.0f,0.0f));
	backgroundSprite_->Draw();


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
	for (size_t y = 0; y < csvData_.size(); y++) {
		for (size_t x = 0; x < csvData_[y].size(); x++) {
			if (panelData_[y][x].isCorrect) {
#pragma region 上のパネルチェック
				// パネルの上が正しいかどうか
				if (y > 0) { // yが0より大きい場合のみアクセス
					if (panelData_[y - 1][x].date != PanelType::Blank) {
						// if (csvData_[y - 1][x] == answerData_[y - 1][x]) {
						//	panelData_[y - 1][x].isCorrect = true;
						// } else {
						//	panelData_[y - 1][x].isCorrect = false;
						// }

						// LPanelかLockLPanelなら上のパネルをチェック
						if (panelData_[y][x].date == PanelType::LPanel || panelData_[y][x].date == PanelType::LockLPanel) {
							if (csvData_[y - 1][x] == answerData_[y - 1][x]) {
								panelData_[y - 1][x].isCorrect = true;
							} else {
								panelData_[y - 1][x].isCorrect = false;
							}
						}

						// UpReverseTPanelかLockUpReverseTPanelなら上のパネルをチェック
						if (panelData_[y][x].date == PanelType::UpReverseTPanel || panelData_[y][x].date == PanelType::LockUpReverseTPanel) {
							if (csvData_[y - 1][x] == answerData_[y - 1][x]) {
								panelData_[y - 1][x].isCorrect = true;
							} else {
								panelData_[y - 1][x].isCorrect = false;
							}
						}

						// InvertedLか LockInvertedLなら上のパネルをチェック
						if (panelData_[y][x].date == PanelType::InvertedL || panelData_[y][x].date == PanelType::LockInvertedL) {
							if (csvData_[y - 1][x] == answerData_[y - 1][x]) {
								panelData_[y - 1][x].isCorrect = true;
							} else {
								panelData_[y - 1][x].isCorrect = false;
							}
						}

						// IPanelかLockIPanelなら上のパネルをチェック
						if (panelData_[y][x].date == PanelType::IPanel || panelData_[y][x].date == PanelType::LockIPanel) {
							if (csvData_[y - 1][x] == answerData_[y - 1][x]) {
								panelData_[y - 1][x].isCorrect = true;
							} else {
								panelData_[y - 1][x].isCorrect = false;
							}
						}

						// PlusPanelかLockPlusPanelなら上のパネルをチェック
						if (panelData_[y][x].date == PanelType::PlusPanel || panelData_[y][x].date == PanelType::LockPlusPanel) {
							if (csvData_[y - 1][x] == answerData_[y - 1][x]) {
								panelData_[y - 1][x].isCorrect = true;
							} else {
								panelData_[y - 1][x].isCorrect = false;
							}
						}

						// LeftRotateTPanelかLockLeftRotateTPanelなら上のパネルをチェック
						if (panelData_[y][x].date == PanelType::LeftRotateTPanel || panelData_[y][x].date == PanelType::LockLeftRotateTPanel) {
							if (csvData_[y - 1][x] == answerData_[y - 1][x]) {
								panelData_[y - 1][x].isCorrect = true;
							} else {
								panelData_[y - 1][x].isCorrect = false;
							}
						}

						// RiteRotateTPanelかLockRiteRotateTPanelなら上のパネルをチェック
						if (panelData_[y][x].date == PanelType::RiteRotateTPanel || panelData_[y][x].date == PanelType::LockRiteRotateTPanel) {
							if (csvData_[y - 1][x] == answerData_[y - 1][x]) {
								panelData_[y - 1][x].isCorrect = true;
							} else {
								panelData_[y - 1][x].isCorrect = false;
							}
						}
					}
				}
#pragma endregion

#pragma region 下のパネルチェック
				// パネルの下が正しいかどうか
				if (y < csvData_.size() - 1) { // yが最終行より小さい場合のみアクセス
					if (panelData_[y + 1][x].date != PanelType::Blank) {
						// if (csvData_[y + 1][x] == answerData_[y + 1][x]) {
						//	panelData_[y + 1][x].isCorrect = true;
						// } else {
						//	panelData_[y + 1][x].isCorrect = false;
						// }

						// パネルがStartPanelなら下のパネルをチェック
						if (panelData_[y][x].date == PanelType::StartPanel) {
							if (csvData_[y + 1][x] == answerData_[y + 1][x]) {
								panelData_[y + 1][x].isCorrect = true;
							} else {
								panelData_[y + 1][x].isCorrect = false;
							}
						}

						// パネルがTPanelかLockTPanelなら下のパネルをチェック
						if (panelData_[y][x].date == PanelType::TPanel || panelData_[y][x].date == PanelType::LockTPanel) {
							if (csvData_[y + 1][x] == answerData_[y + 1][x]) {
								panelData_[y + 1][x].isCorrect = true;
							} else {
								panelData_[y + 1][x].isCorrect = false;
							}
						}

						// パネルがIPanelかLockIPanelなら下のパネルをチェック
						if (panelData_[y][x].date == PanelType::IPanel || panelData_[y][x].date == PanelType::LockIPanel) {
							if (csvData_[y + 1][x] == answerData_[y + 1][x]) {
								panelData_[y + 1][x].isCorrect = true;
							} else {
								panelData_[y + 1][x].isCorrect = false;
							}
						}

						// パネルがUpReverseLPanelかLockUpReverseLPanelなら下のパネルをチェック
						if (panelData_[y][x].date == PanelType::UpReverseLPanel || panelData_[y][x].date == PanelType::LockUpReverseLPanel) {
							if (csvData_[y + 1][x] == answerData_[y + 1][x]) {
								panelData_[y + 1][x].isCorrect = true;
							} else {
								panelData_[y + 1][x].isCorrect = false;
							}
						}

						// パネルがUpInvertedLPanelかLockUpInvertedLPanelなら下のパネルをチェック
						if (panelData_[y][x].date == PanelType::UpInvertedLPanel || panelData_[y][x].date == PanelType::LockUpInvertedLPanel) {
							if (csvData_[y + 1][x] == answerData_[y + 1][x]) {
								panelData_[y + 1][x].isCorrect = true;
							} else {
								panelData_[y + 1][x].isCorrect = false;
							}
						}

						// パネルがPlusPanelかLockPlusPanelなら下のパネルをチェック
						if (panelData_[y][x].date == PanelType::PlusPanel || panelData_[y][x].date == PanelType::LockPlusPanel) {
							if (csvData_[y + 1][x] == answerData_[y + 1][x]) {
								panelData_[y + 1][x].isCorrect = true;
							} else {
								panelData_[y + 1][x].isCorrect = false;
							}
						}

						// パネルがLeftRotateTPanelかLockLeftRotateTPanelなら下のパネルをチェック
						if (panelData_[y][x].date == PanelType::LeftRotateTPanel || panelData_[y][x].date == PanelType::LockLeftRotateTPanel) {
							if (csvData_[y + 1][x] == answerData_[y + 1][x]) {
								panelData_[y + 1][x].isCorrect = true;
							} else {
								panelData_[y + 1][x].isCorrect = false;
							}
						}

						// パネルがRiteRotateTPanelかLockRiteRotateTPanelなら下のパネルをチェック
						if (panelData_[y][x].date == PanelType::RiteRotateTPanel || panelData_[y][x].date == PanelType::LockRiteRotateTPanel) {
							if (csvData_[y + 1][x] == answerData_[y + 1][x]) {
								panelData_[y + 1][x].isCorrect = true;
							} else {
								panelData_[y + 1][x].isCorrect = false;
							}
						}
					}
				}
#pragma endregion

#pragma region 左のパネルチェック
				// パネルの左が正しいかどうか
				if (x > 0) { // xが0より大きい場合のみアクセス
					if (panelData_[y][x - 1].date != PanelType::Blank) {
						// if (csvData_[y][x - 1] == answerData_[y][x - 1]) {
						//	panelData_[y][x - 1].isCorrect = true;
						// } else {
						//	panelData_[y][x - 1].isCorrect = false;
						// }

						// パネルがTPanelかLockTPanelなら左のパネルをチェック
						if (panelData_[y][x].date == PanelType::TPanel || panelData_[y][x].date == PanelType::LockTPanel) {
							if (csvData_[y][x - 1] == answerData_[y][x - 1]) {
								panelData_[y][x - 1].isCorrect = true;
							} else {
								panelData_[y][x - 1].isCorrect = false;
							}
						}

						// パネルがUpReverseTPanelかLockUpReverseTPanelなら左のパネルをチェック
						if (panelData_[y][x].date == PanelType::UpReverseTPanel || panelData_[y][x].date == PanelType::LockUpReverseTPanel) {
							if (csvData_[y][x - 1] == answerData_[y][x - 1]) {
								panelData_[y][x - 1].isCorrect = true;
							} else {
								panelData_[y][x - 1].isCorrect = false;
							}
						}

						// パネルがRiteRotateTPanelかLockRiteRotateTPanelなら左のパネルをチェック
						if (panelData_[y][x].date == PanelType::RiteRotateTPanel || panelData_[y][x].date == PanelType::LockRiteRotateTPanel) {
							if (csvData_[y][x - 1] == answerData_[y][x - 1]) {
								panelData_[y][x - 1].isCorrect = true;
							} else {
								panelData_[y][x - 1].isCorrect = false;
							}
						}
						

						// UpReverseLPanelかLockUpReverseLPanelなら左のパネルをチェック
						if (panelData_[y][x].date == PanelType::UpReverseLPanel || panelData_[y][x].date == PanelType::LockUpReverseLPanel) {
							if (csvData_[y][x - 1] == answerData_[y][x - 1]) {
								panelData_[y][x - 1].isCorrect = true;
							} else {
								panelData_[y][x - 1].isCorrect = false;
							}
						}

						// InvertedLかLockInvertedLなら左のパネルをチェック
						if (panelData_[y][x].date == PanelType::InvertedL || panelData_[y][x].date == PanelType::LockInvertedL) {
							if (csvData_[y][x - 1] == answerData_[y][x - 1]) {
								panelData_[y][x - 1].isCorrect = true;
							} else {
								panelData_[y][x - 1].isCorrect = false;
							}
						}

						// PlusPanelかLockPlusPanelなら左のパネルをチェック
						if (panelData_[y][x].date == PanelType::PlusPanel || panelData_[y][x].date == PanelType::LockPlusPanel) {
							if (csvData_[y][x - 1] == answerData_[y][x - 1]) {
								panelData_[y][x - 1].isCorrect = true;
							} else {
								panelData_[y][x - 1].isCorrect = false;
							}
						}

						// MinusPanelかLockMinusPanelなら左のパネルをチェック
						if (panelData_[y][x].date == PanelType::MinusPanel || panelData_[y][x].date == PanelType::LockMinusPanel) {
							if (csvData_[y][x - 1] == answerData_[y][x - 1]) {
								panelData_[y][x - 1].isCorrect = true;
							} else {
								panelData_[y][x - 1].isCorrect = false;
							}
						}
					}
				}

#pragma endregion

#pragma region 右のパネルチェック
				// パネルの右が正しいかどうか
				if (x < csvData_[y].size() - 1) { // xが最終列より小さい場合のみアクセス
					if (panelData_[y][x + 1].date != PanelType::Blank) {
						//if (csvData_[y][x + 1] == answerData_[y][x + 1]) {
						//	panelData_[y][x + 1].isCorrect = true;
						//} else {
						//	panelData_[y][x + 1].isCorrect = false;
						//}

						// パネルがTPanelかLockTPanelなら右のパネルをチェック
						if (panelData_[y][x].date == PanelType::TPanel || panelData_[y][x].date == PanelType::LockTPanel) {
							if (csvData_[y][x + 1] == answerData_[y][x + 1]) {
								panelData_[y][x + 1].isCorrect = true;
							} else {
								panelData_[y][x + 1].isCorrect = false;
							}
						}

						// パネルがUpReverseTPanelかLockUpReverseTPanelなら右のパネルをチェック
						if (panelData_[y][x].date == PanelType::UpReverseTPanel || panelData_[y][x].date == PanelType::LockUpReverseTPanel) {
							if (csvData_[y][x + 1] == answerData_[y][x + 1]) {
								panelData_[y][x + 1].isCorrect = true;
							} else {
								panelData_[y][x + 1].isCorrect = false;
							}
						}

						// パネルがLeftRotateTPanelかLockLeftRotateTPanelなら右のパネルをチェック
						if (panelData_[y][x].date == PanelType::LeftRotateTPanel || panelData_[y][x].date == PanelType::LockLeftRotateTPanel) {
							if (csvData_[y][x + 1] == answerData_[y][x + 1]) {
								panelData_[y][x + 1].isCorrect = true;
							} else {
								panelData_[y][x + 1].isCorrect = false;
							}
						}


						// パネルがUpReverseLPanelかLockUpReverseLPanelなら右のパネルをチェック
						if (panelData_[y][x].date == PanelType::UpReverseLPanel || panelData_[y][x].date == PanelType::LockUpReverseLPanel) {
							if (csvData_[y][x + 1] == answerData_[y][x + 1]) {
								panelData_[y][x + 1].isCorrect = true;
							} else {
								panelData_[y][x + 1].isCorrect = false;
							}
						}

						// パネルがLPanelかLockLPanelなら右のパネルをチェック
						if (panelData_[y][x].date == PanelType::LPanel || panelData_[y][x].date == PanelType::LockLPanel) {
							if (csvData_[y][x + 1] == answerData_[y][x + 1]) {
								panelData_[y][x + 1].isCorrect = true;
							} else {
								panelData_[y][x + 1].isCorrect = false;
							}
						}

						// パネルがPlusPanelかLockPlusPanelなら右のパネルをチェック
						if (panelData_[y][x].date == PanelType::PlusPanel || panelData_[y][x].date == PanelType::LockPlusPanel) {
							if (csvData_[y][x + 1] == answerData_[y][x + 1]) {
								panelData_[y][x + 1].isCorrect = true;
							} else {
								panelData_[y][x + 1].isCorrect = false;
							}
						}

						// パネルがMinusPanelかLockMinusPanelなら右のパネルをチェック
						if (panelData_[y][x].date == PanelType::MinusPanel || panelData_[y][x].date == PanelType::LockMinusPanel) {
							if (csvData_[y][x + 1] == answerData_[y][x + 1]) {
								panelData_[y][x + 1].isCorrect = true;
							} else {
								panelData_[y][x + 1].isCorrect = false;
							}
						}

					}
				}
			}
#pragma endregion

			//if (panelData_[y][x].date == PanelType::GoalPanel) {
			//	if (!panelData_[y - 1][x].isCorrect) {
			//		panelData_[y][x].isCorrect = false;
			//	}
			//}
		}
	}
}