#include "Puzzle15.h"


using namespace KamataEngine;

Puzzle15::Puzzle15() {}

Puzzle15::~Puzzle15() {}

void Puzzle15::Initialize() {
	// 乱数生成器を初期化
	std::random_device rd;
	randomSeed.seed(rd());
	std::uniform_real_distribution<float> randomFloat(-12.0f, 12.0f);

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
		panelData.pos = {randomFloat(randomSeed) * 30.0f + 640.0f, randomFloat(randomSeed) * 20.0f + 320.0f};

		// パネルのスプライトを作成
		Sprite* panelDate = Sprite::Create(panelTextures_[i], panelData.pos);
		panelDate->SetAnchorPoint(Vector2(0.5f, 0.5f));
		panelData.sprite = panelDate;
		panelData_.push_back(panelData);
	}

	fileAccessor_ = nullptr;
	fileAccessor_ = new FileJson::FileAccessor("Resources/Puzzle15/Puzzle15.json");

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
			UpdatePanelData();
		}
	}

	DrawImGui();
}

void Puzzle15::Draw() {}

void Puzzle15::SpriteDraw() {
	// 全てのパネルを描画
	for (size_t i = 0; i < panelData_.size(); i++) {
		panelData_[i].sprite->Draw();
	}
}

void Puzzle15::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("puzzle15");
	ImGui::Text("puzzle15,UpDate,OK");
	ImGui::DragFloat2("mousePos", &mousePos.x, 0.1f);
	ImGui::Text("selectedPanelIndex_ : %d", HoldIndex); // 選択されているパネルのインデックスをデバッグ表示
	ImGui::End();
#endif // _DEBUG
}

// パネルデータの更新
void Puzzle15::UpdatePanelData() {
	// 全てのパネルに対して処理
	for (int i = 0; i < panelData_.size(); i++) {
		// スプライトの座標とサイズを取得
		Vector2 spritePos = panelData_[i].sprite->GetPosition();
		Vector2 spriteSize = panelData_[i].sprite->GetSize();
		// マウスの座標がスプライトの範囲内にあるか判定
		if (mousePos.x >= spritePos.x - spriteSize.x / 2 && mousePos.x <= spritePos.x + spriteSize.x / 2) {
			if (mousePos.y >= spritePos.y - spriteSize.y / 2 && mousePos.y <= spritePos.y + spriteSize.y / 2) {
				// 同じパネルでないかの判定(この条件式は常に真になるので削除する必要がある)
				if (panelData_[i].date != panelData_[i].date) {
					// パネルの位置を更新
					panelData_[i].pos = mousePos;
				}
			}
		}
	}
	HoldIndex = -1; // 選択されたパネルのインデックスをリセット
}