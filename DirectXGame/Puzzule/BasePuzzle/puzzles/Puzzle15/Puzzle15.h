#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "../../../LoadJsonFile/FileJson.h"
#include "../../BasePuzzle.h"
#include "../../../../IntVector2.h"
#include "NumberSprite.h"
// パネルの種類を定義するenumクラス
enum class PanelType {
	Blank,   // 空白0
	Panle1,  // 1Panel
	Panel2,  // 2Panel
	Panel3,  // 3Panel
	Panel4,  // 4Panel
	Panel5,  // 5Panel
	Panel6,  // 6Panel
	Panel7,  // 7Panel
	Panel8,  // 8Panel
	Panel9,  // 9Panel
	Panle10, // 10Panel
	Panel11, // 11Panel
	Panel12, // 12Panel
	Panel13, // 13Panel
	Panel14, // 14Panel
	Panel15, // 15Panel
};
// パネルのデータを保持する構造体
struct PanelData {
	// パネルの配置データ
	PanelType date;
	Sprite* sprite;
};

class Puzzle15 : public BasePuzzle {
public:
	// コンストラクタ
	Puzzle15();
	// デストラクタ
	~Puzzle15();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;
	// Sprite描画
	void SpriteDraw() override;

private:
	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui() override;

	// パネルデータの変更
	void ChangePanelData();
	// パネルデータの再生成
	void ReCreateCsvData();

private:
	// 空白のスプライト
	Sprite* blankSprite;
	// パネルのサイズ
	Vector3 panelSize_;
	// パネルのテクスチャ
	uint32_t panelTexture_;
	// パネルのデータ
	std::vector<std::vector<PanelData>> panelData_;
	// CSVデータ
	std::vector<std::vector<int>> csvData_;
	std::vector<std::vector<int>> answerData_;
	// holdしているパネルの位置
	IntVector2 holdPos_;
	
	// Json読み書き用のファイルアクセサ
	FileJson::FileAccessor* fileAccessor_;
	// クリックされたパネルのインデックスを保持する変数
	int selectedSpriteIndex = -1;

	// 数字スプライト
	std::vector<NumberSprite> numberSprite;

	// クリアフラグ
	bool isClear_;
	//　ホールドしているか
	bool isHold_;


};
