#pragma once
#include "../../../../IntVector2.h"
#include "../../../LoadJsonFile/FileJson.h"
#include "../../BasePuzzle.h"
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

// パネルの種類を定義するenumクラス
enum class PanelType {
	Blank,                // 空白0
	StartPanel,           // Startパネル1
	TPanel,               // T型パネル2
	LPanel,               // L型パネル3
	InvertedL,            // 上下逆L型パネル4
	IPanel,               // I型パネル5
	UpReverseLPanel,      // 「型パネル6
	UpInvertedLPanel,     // 」型パネル7
	UpReverseTPanel,      // 逆T型パネル8
	GoalPanel,            // Goalパネル9
	PlusPanel,            // +型パネル10
	LeftRotateTPanel,     // 左回転T型パネル11
	RiteRotateTPanel,     // 右回転T型パネル12
	MinusPanel,           // -型パネル13
	LockTPanel,           // 固定T型パネル14
	LockLPanel,           // 固定L型パネル15
	LockInvertedL,        // 固定上下逆L型パネル16
	LockIPanel,           // 固定I型パネル17
	LockUpReverseLPanel,  // 固定「型パネル18
	LockUpInvertedLPanel, // 固定」型パネル19
	LockUpReverseTPanel,  // 固定逆T型パネル20
	LockPlusPanel,        // 固定+型パネル21
	LockLeftRotateTPanel, // 固定左回転T型パネル22
	LockRiteRotateTPanel, // 固定右回転T型パネル23
	LockMinusPanel,       // 固定-型パネル24
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

	//パネルを中心に移動させるVector2
	Vector2 centor_;

	// パネルサイズ
	Vector3 panelSize_;
	// クリアフラグ
	bool isClear_;
	// 時間
	int time_;
	// ホールドしているか
	bool isHold_ = false;
	// 乱数シード
	std::mt19937 randomSeed;
};