// Puzzle15.cpp
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
	std::random_device rd; // 乱数の種を生成
	randomSeed.seed(rd()); // メルセンヌ・ツイスタ乱数生成器に種を設定

	// テクスチャのロード
	panelTexture_ = TextureManager::Load("Puzzle15/panel.png"); // 枠線のテクスチャ
	for (size_t i = 1; i <= 15; i++) {
		// 1から15までの数字パネルのテクスチャをロード
		panelTextures_.push_back(TextureManager::Load("Puzzle15/puzzle15_" + std::to_string(i) + ".png"));
	}

	//flameTexture_ = TextureManager::Load("Puzzle15/puzzleFlame.png");
	flameSprite = Sprite::Create(flameTexture_, {0.0f, 0.0f}); // ここを修正

	// FileAccessorの初期化
	fileAccessor_ = nullptr;

	// JSONファイル名を指定してFileAccessorを初期化
	fileAccessor_ = new FileJson::FileAccessor("Resources/Puzzle15/Panel15.json");

	// JSONからパネルサイズ、クリアフラグ、CSVデータを読み込む
	panelSize_ = fileAccessor_->ReadVector3("Puzzle15", "size", Vector3()); // パネルサイズを読み込む
	isClear_ = fileAccessor_->Read("Puzzle15", "isClear", bool());          // クリアフラグを読み込む
	csvData_ = fileAccessor_->ReadCsvData("Puzzle15", "start");             // 初期配置を読み込む
	answerData_ = fileAccessor_->ReadCsvData("Puzzle15", "answer");         // 解答データを読み込む

	// 空白パネルのスプライトを作成
	blankSprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));

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
			// パネルの座標を更新
			panelData_[y][x].sprite->SetPosition({static_cast<float>(x * panelSize_.x + panelSize_.x * 0.5f+500.0f), static_cast<float>(y * panelSize_.y + panelSize_.y * 0.5f+200.0f)});
		}
	}

	// ホールドされていない場合
	if (!isHold_) {
		// マウスの左ボタンが押された場合
		if (input_->IsTriggerMouse(0)) {
			// 全てのパネルをチェック
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
							isHold_ = true; // ホールド状態にする
						}
					}
				}
			}
		}
	}
	// ホールドされている場合
	else {
		// マウスの左ボタンが押されている場合
		if (input_->IsPressMouse(0)) {
			// ドラッグ中のスプライトの位置を更新
			panelData_[holdPos_.y][holdPos_.x].sprite->SetPosition(mousePos);
		}
		// マウスの左ボタンが離された場合
		if (input_->IsReleseMouse(0)) {
			UpdatePanelData(); // パネルデータを更新
		}
	}

	CheckClear(); // クリアチェック
	DrawImGui();  // ImGuiの描画
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

	flameSprite->Draw();

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
	panelData_.resize(csvData_.size());

	for (int y = 0; y < panelData_.size(); y++) {
		panelData_[y].resize(csvData_[y].size());
		for (int x = 0; x < panelData_[y].size(); x++) {
			int panelNumber = csvData_[y][x]; // CSVデータからパネル番号を取得

			Vector2 position = {static_cast<float>(x) * 100.0f + 500.0f, static_cast<float>(y) * 100.0f + 150.0f}; // パネルの座標を計算

			if (panelNumber == 0) {
				// 空白パネル
				panelData_[y][x].date = PanelType::Blank;
				// パネルの種類を空白に設定
				Sprite* sprite = Sprite::Create(panelTexture_, Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f)); // スプライト作成
				// アンカーポイント設定
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f));
				// スプライトの位置を設定
				sprite->SetPosition(position);
				// スプライトをPanelDataに格納
				panelData_[y][x].sprite = sprite;
			} else {
				// 数字パネル
				// PanelTypeにキャスト
				panelData_[y][x].date = static_cast<PanelType>(panelNumber);
				Sprite* sprite = Sprite::Create(panelTextures_[panelNumber - 1], Vector2(panelSize_.x + panelSize_.x * 0.5f, panelSize_.y + panelSize_.y * 0.5f));
				// アンカーポイント設定
				sprite->SetAnchorPoint(Vector2(0.5f, 0.5f));
				// 数字スプライトの位置を設定
				sprite->SetPosition(position);
				panelData_[y][x].sprite = sprite;
			}
		}
	}
}

// CSVデータを再生成する関数（ランダムな初期配置を生成）
//void Puzzle15::ReCreateCsvData() {
//
//	// AnswerDataを初期化
//	answerData_.resize(4);
//	int number = 1;
//	for (size_t y = 0; y < answerData_.size(); y++) {
//		answerData_[y].resize(4);
//		for (size_t x = 0; x < answerData_[y].size(); x++) {
//			if (number <= 15) {
//				answerData_[y][x] = number++;
//			} else {
//				answerData_[y][x] = 0; // 最後の要素は0
//			}
//		}
//	}
//	// CSVファイルに書き込む
//	fileAccessor_->WriteCsvData("Puzzle15", "answer", answerData_);
//	fileAccessor_->Save();
//}

// パネルデータの更新関数
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

						// CSVファイルに書き込む
						fileAccessor_->WriteCsvData("Puzzle15", "panel", csvData_);
					}
				}
			}
		}
	}
	isHold_ = false; // ホールドを解除
}

// クリアチェック関数
void Puzzle15::CheckClear() {
	// answerDataとcsvDataを比較してクリアしているか判定
	for (size_t y = 0; y < answerData_.size(); y++) {
		for (size_t x = 0; x < answerData_[y].size(); x++) {
			if (answerData_[y][x] != csvData_[y][x]) {
				isClear_ = false; // クリアしていない
				return;           // 関数を抜ける
			} else {
				isClear_ = true; // クリアしている
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
	fileAccessor_->Save(); // ファイルを保存
}