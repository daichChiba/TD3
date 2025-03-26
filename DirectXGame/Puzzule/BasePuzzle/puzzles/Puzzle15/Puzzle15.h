#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "../../BasePuzzle.h"
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

private:
};
