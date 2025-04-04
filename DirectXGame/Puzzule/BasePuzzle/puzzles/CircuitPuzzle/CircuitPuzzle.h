#pragma once
#include "../../../../IntVector2.h"
#include "../../../LoadJsonFile/FileJson.h"
#include "../../BasePuzzle.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

// パネルの種類を定義するenumクラス
enum class PanelType {
	Blank,            // 空白0
	StartPanel,       // Startパネル1
	TPanel,           // T型パネル2
	LPanel,           // L型パネル3
	InvertedL,        // 上下逆L型パネル4
	IPanel,           // I型パネル5
	UpReverseLPanel,  // 「型パネル6
	UpInvertedLPanel, // 」型パネル7
	UpReverseTPanel,  // 逆T型パネル8
	GoalPanel,         // Goalパネル9
	LeftRotateTPanel, // 左回転T型パネル10
	RiteRotateTPanel, // 右回転T型パネル11
	MinusPanel,       // -型パネル12
	PlusPanel,        // +型パネル13
};

// パネルのデータを保持する構造体
struct PanelData {
	// パネルの配置データ
	PanelType date;
	Sprite* sprite;
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
	// answerDataと比較してクリアしているか判定
	void CheckClear();
	// ImGui描画
	void DrawImGui() override;

	// パネルデータの変更
	void ChangePanelData();

	void UpdatePanelData();

private:
	// パネルデータ
	std::vector<std::vector<PanelData>> panelData_;
	// パネルホールド位置
	IntVector2 holdPos_;
	// Csvデータ
	std::vector<std::vector<int>> csvData_;
	std::vector<std::vector<int>> answerData_;

	// Json読み書き用のファイルアクセサ
	FileJson::FileAccessor* fileAccessor_;



	// クリックされたパネルのインデックスを保持する変数
	int selectedSpriteIndex = -1;
	// パネルのテクスチャ
	uint32_t panelTexture_;
	std::vector<uint32_t> panelTextures_;
	// パネルのスプライト

	// パネルサイズ
	Vector3 panelSize_;
	// クリアフラグ
	bool isClear_;
	// 時間
	int time_;
	// ホールドしているか
	bool isHold_ = false;
};