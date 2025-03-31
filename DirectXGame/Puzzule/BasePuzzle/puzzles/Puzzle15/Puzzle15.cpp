#include "Puzzle15.h"

// コンストラクタ
Puzzle15::Puzzle15() {}

// デストラクタ
Puzzle15::~Puzzle15() {
	// FileAccessorの解放
	if (fileAccessor_) {
		delete fileAccessor_;    // FileAccessorのインスタンスを解放
		fileAccessor_ = nullptr; // 解放後にnullptrを設定
	}
}

// 初期化関数
void Puzzle15::Initialize() {
	std::random_device rd; // 乱数の種
	randomSeed.seed(rd()); // メルセンヌ・ツイスタの初期化
	panelTexture_ = TextureManager::Load("Puzzle15/panel.png");

	// FileAccessorの初期化
	fileAccessor_ = nullptr; // 初期化

	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/Puzzle15/Panel15.json");

	// JSONからパネルサイズを読み込む
	panelSize_ = fileAccessor_->ReadVector3("Puzzle15", "size", Vector3());

	// JSONからisCompleteを読み込む
	isClear_ = fileAccessor_->Read("Puzzle15", "isClear", bool());

	// JSONからCSVデータを読み込む
	csvData_ = fileAccessor_->ReadCsvData("Puzzle15", "start");     // 初期配置を読み込み
	answerData_ = fileAccessor_->ReadCsvData("Puzzle15", "answer"); // 解答データを読み込み

	blankSprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f)); // 空白パネルのスプライト作成
	for (size_t i = 1; i <= 15; i++) {
		panelTextures_.push_back(TextureManager::Load("Puzzle15/puzzle15_" + std::to_string(i) + ".png"));
	}

	// CSVデータを再生成（初期配置をランダムに生成）
	ReCreateCsvData();
	// パネルデータの変更（CSVデータに基づいてパネル情報を設定）
	ChangePanelData();

	BasePuzzle::Initialize(); // 親クラスの初期化処理
}

// 更新関数
void Puzzle15::Update() {
	// マウス座標の取得
	mousePos = input_->GetMousePosition();

	// パネルデータの更新
	for (size_t y = 0; y < panelData_.size(); y++) {
		for (size_t x = 0; x < panelData_[y].size(); x++) {
			// パネルが空白でない場合

			// パネルの座標を更新
			panelData_[y][x].sprite->SetPosition({static_cast<float>(x * panelSize_.x + panelSize_.x * 0.5f), static_cast<float>(y * panelSize_.y + panelSize_.y * 0.5f)});
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

	CheckClear();
	// ImGuiの描画処理
	DrawImGui();
}

// 描画関数（3D描画）
void Puzzle15::Draw() {}

// スプライト描画関数（2D描画）
void Puzzle15::SpriteDraw() {
	// CSVデータに基づいて画像を描画
	for (size_t y = 0; y < panelData_.size(); y++) {
		for (size_t x = 0; x < panelData_[y].size(); x++) {
			if (panelData_[y][x].date != PanelType::Blank) { // 空白パネル以外を描画
				if (panelData_[y][x].sprite != nullptr) {
					// スプライト描画
					panelData_[y][x].sprite->Draw(); // パネルのスプライト描画
				}
			}
		}
	}

	// NumberSpriteの描画
	// for (size_t i = 0; i < numberSprite.size(); i++) {
	//	numberSprite[i].Draw(); // 数字スプライト描画
	//}
}

// ImGuiの描画関数
void Puzzle15::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("puzzle15");                         // ImGuiウィンドウ開始
	ImGui::Text("puzzle15,UpDate,OK");                // テキスト表示
	ImGui::DragFloat2("mousePos", &mousePos.x, 0.1f); // マウス座標の表示・操作
	if (isClear_) {
		ImGui::Text("Clear!!");
	} else {
		ImGui::Text("Not Clear");
	}
	ImGui::End(); // ImGuiウィンドウ終了
#endif            // _DEBUG
}

// パネルデータの変更関数
void Puzzle15::ChangePanelData() {
	// CSVデータをPanelDataに変換
	panelData_.resize(csvData_.size()); // PanelDataのサイズをCSVデータに合わせる

	// NumberSpriteを初期化
	// for (int i = 0; i < 15; i++) {
	//	NumberSprite number;            // NumberSpriteのインスタンスを作成
	//	number.Initialize(Vector2());   // 初期化
	//	numberSprite.push_back(number); // ベクターに追加
	//}

	for (int y = 0; y < panelData_.size(); y++) {
		panelData_[y].resize(csvData_[y].size()); // 各行のサイズをCSVデータに合わせる
		for (int x = 0; x < panelData_[y].size(); x++) {
			int panelNumber = csvData_[y][x]; // CSVデータからパネル番号を取得

			Vector2 position = {static_cast<float>(x) * 100.0f + 500.0f, static_cast<float>(y) * 100.0f + 150.0f}; // パネルの座標を計算

			if (panelNumber == 0) {
				// 空白パネル
				panelData_[y][x].date = PanelType::Blank;                                                                                        // パネルの種類を空白に設定
				Sprite* sprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f)); // スプライト作成
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f));                                                                                     // アンカーポイント設定
				sprite->SetPosition(position);                                                                                                   // スプライトの位置を設定
				panelData_[y][x].sprite = sprite;                                                                                                // スプライトをPanelDataに格納
			} else {
				// 数字パネル
				panelData_[y][x].date = static_cast<PanelType>(panelNumber); // PanelTypeにキャスト
				Sprite* sprite = Sprite::Create(panelTextures_[panelNumber - 1], Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f)); // アンカーポイント設定
				sprite->SetPosition(position); // 数字スプライトの位置を設定
				panelData_[y][x].sprite = sprite;

				// TODO : GetSpriteで指定している番号が常に0で良いか確認
				//  (numberSprite[i]が常に1つのスプライトしか保持していないなら問題ない)
			}
		}
	}
}
// CSVデータを再生成する関数（ランダムな初期配置を生成）
void Puzzle15::ReCreateCsvData() {
	// CSVデータのサイズを4x4に設定
	csvData_.resize(4);
	// 0から15までの乱数を生成
	std::uniform_int_distribution<int> random(0, 15);

	for (int y = 0; y < csvData_.size(); y++) {
		for (int x = 0; x < csvData_[y].size(); x++) {
			// 初期値を-1に設定
			csvData_[y][x] = -1;
		}
	}
	// パネルの配置データを初期化し0~15までの数字をランダムに配置
	for (int y = 0; y < csvData_.size(); y++) {
		for (int x = 0; x < csvData_[y].size(); x++) {
			bool is = true; // フラグ初期化
			while (is) {
				is = false; // 一度falseに設定
				// 乱数生成
				csvData_[y][x] = random(randomSeed); // 乱数生成

				// 同じ数字がある場合は再度乱数を生成
				for (int i = 0; i < csvData_.size(); i++) {
					for (int j = 0; j < csvData_[i].size(); j++) {
						if (!(i == y && j == x)) {                  // 自分自身を除く
							if (csvData_[i][j] == csvData_[y][x]) { // 同じ数字があるか確認
								is = true;                          // 同じ数字があればtrueに戻す
							}
						}
					}
				}
			}
		}
	}
	answerData_.resize(4);
	int number = 1;
	for (size_t y = 0; y < answerData_.size(); y++) {
		answerData_[y].resize(4);
		for (size_t x = 0; x < answerData_[y].size(); x++) {
			if (number <= 15) {
				answerData_[y][x] = number++;
			} else {
				answerData_[y][x] = 0; // 最後の要素は0
			}
		}
	}
	fileAccessor_->WriteCsvData("Puzzle15", "answer", answerData_);
	fileAccessor_->Save();
}

void Puzzle15::UpdatePanelData() {
	for (size_t y = 0; y < panelData_.size(); y++) {
		for (size_t x = 0; x < panelData_[y].size(); x++) {
			Vector2 spritePos = panelData_[y][x].sprite->GetPosition();
			Vector2 spriteSize = {panelSize_.x, panelSize_.y};
			if (mousePos.x >= spritePos.x - spriteSize.x / 2 && mousePos.x <= spritePos.x + spriteSize.x / 2) {
				if (mousePos.y >= spritePos.y - spriteSize.y / 2 && mousePos.y <= spritePos.y + spriteSize.y / 2) {
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
						fileAccessor_->WriteCsvData("Puzzle15", "panel", csvData_);
					}
				}
			}
		}
	}
	isHold_ = false;
}

void Puzzle15::CheckClear() {
	// answerDataとcsvDataを比較してクリアしているか判定
	for (size_t y = 0; y < answerData_.size(); y++) {
		for (size_t x = 0; x < answerData_[y].size(); x++) {
			if (answerData_[y][x] != csvData_[y][x]) {
				isClear_ = false;
				return;
			} else {
				isClear_ = true;
			}
		}
	}

	if (isClear_) {
		// クリアした場合
		fileAccessor_->Write("Puzzle15", "isClear", true);
	} else {
		// クリアしていない場合
		fileAccessor_->Write("Puzzle15", "isClear", false);
	}
	fileAccessor_->Save();
}
