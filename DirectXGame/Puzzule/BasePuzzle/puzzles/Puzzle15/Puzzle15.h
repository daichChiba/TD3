#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "../../BasePuzzle.h"
#include "../../../../etc/IntVector2.h"
#include "Puzzule/LoadJsonFile/FileJson.h"
#include <iostream>
#include <random>
#include <vector>

class Puzzle15 : public BasePuzzle {
public:
	// パネルの種類
	enum class PanelType {
		Blank, panel1, panel2, panel3,
		panel4, panel5, panel6, panel7,
		panel8, panel9, panel10, panel11,
		panel12, panel13, panel14, panel15
	};

	// パネルのデータ構造
	struct PanelDate {
		PanelType date;     // パネルの種類
		Sprite* sprite;     // パネルのスプライト
		Vector2 pos;        // パネルの位置
		Vector2 prePos; // パネルの初期位置
		int blackPanelIndex = -1; // 黒いパネルのインデックス
		int preBlackPanelIndex = -1; // 前の黒いパネルのインデックス
	};
	struct BlackPanelDate {
		Sprite* sprite; // 黒いパネルのスプライト
		bool isLock;    // 黒いパネルのロック状態
	};

	Puzzle15();
	~Puzzle15();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
	/// <summary>
	/// スプライト描画
	/// </summary>
	void SpriteDraw() override;

private:
	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui() override;

	/// <summary>
	/// パネルデータの更新
	/// </summary>
	void BlackPanelOnCorision();

	/// <summary>
	/// 黒いパネルがあるかどうかを判定する関数
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	int IsInsideBlackPanel(Vector2 pos,Sprite*& targetBladckPanel);


	void IsClear(int blackPanelIndex);


private:
	// 乱数シード
	std::mt19937 randomSeed;

	// パネルのテクスチャ
	std::vector<uint32_t> panelTextures_;

	// パネルデータ
	std::vector<PanelDate> panelData_;

	// ホールド状態
	bool isHold_ = false;

	// パネルホールド位置
	Vector2 holdPos_;

	// 選択されたパネルのインデックス
	int HoldIndex = -1;

	// パネルを入れるためのcsvData
	std::vector<std::vector<int>> csvData_;
	std::vector<std::vector<int>> clearData;

	// パネルのサイズ
	Vector3 panelSize_;

	// パネルを中心に移動させるVector2
	Vector2 centor_;

	// 黒いテクスチャ(パネルを入れる場所をわかりやすくするために必要なもの)
	uint32_t BlaccTexture_;

	
	uint32_t BackgroundTexture_;
	Sprite* backgroundSprite_;

	// LoadJsonFileのファイルアクセサ
	FileJson::FileAccessor* fileAccessor_ = nullptr;

	// 黒いパネルのスプライトを保持するリスト
	std::vector<BlackPanelDate> BlackPanels;
};