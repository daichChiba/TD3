#include "CircuitPuzzle.h" // CircuitPuzzle.hをインクルード
#include "imgui.h"         // ImGuiのヘッダーファイル

// コンストラクタ
CircuitPuzzle::CircuitPuzzle() {}

// デストラクタ
CircuitPuzzle::~CircuitPuzzle() {
	if (fileAccessor_) {
		delete fileAccessor_; // メモリリークを防ぐためにdelete
		fileAccessor_ = nullptr;
	}
}

// 初期化
void CircuitPuzzle::Initialize() {
	fileAccessor_ = nullptr;
    // JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
    fileAccessor_ = new FileJson::FileAccessor("Puzzule/BasePuzzle/puzzles/CircuitPuzzle/CircuitPuzzle.json");

	// JSONからパネルサイズを読み込む
	panelSize_ = fileAccessor_->ReadVector3("Circuit", "Pos", Vector3());

	// JSONからisPanelを読み込む
	isComplete_ = fileAccessor_->Read("Circuit", "isComplete", bool());
}

// 更新
void CircuitPuzzle::Update() { DrawImGui(); }

// 描画
void CircuitPuzzle::Draw() {}

// ImGui描画
void CircuitPuzzle::DrawImGui() {
#ifdef _DEBUG
	ImGui::Begin("CircuitPuzzle");
	ImGui::Text("CircuitPuzzle,UpDate,OK");

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

	fileAccessor_->Save(); // JSONファイルを保存

	ImGui::End();
#endif
}