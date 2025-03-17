#pragma once
#include "../../../LoadJsonFile/FileJson.h"
#include "../../BasePuzzle.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

// パネルの種類を定義するenumクラス
enum class PanelType {
	Block, // ブロック
	Panel, // パネル
};

// パネルのデータを保持する構造体
struct PanelData {
	// パネルの配置データ
	std::vector<std::vector<PanelType>> date;
};

// 回路パズルクラス
class CircuitPuzzle : public BasePuzzle {
public:
	// コンストラクタ
	CircuitPuzzle();
	// デストラクタ
	~CircuitPuzzle();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;
	// Sprite描画
	void SpriteDraw() override;

private:
	// ImGui描画
	void DrawImGui() override;

private:
	// パネルデータ
	PanelData panelData_;
	// Json読み書き用のファイルアクセサ
	FileJson::FileAccessor* fileAccessor_;

	uint32_t panelTexture_; // パネルのテクスチャ
	std::vector<Sprite*> panelSprites_; // パネルのスプライト


	Vector3 panelSize_; // パネルサイズ
	bool isComplete_;      // パネルフラグ
	int time_;
};