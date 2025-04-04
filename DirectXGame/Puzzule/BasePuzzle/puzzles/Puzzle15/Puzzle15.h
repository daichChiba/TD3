// Puzzle15.h
#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include "../../../../IntVector2.h"
#include "../../../LoadJsonFile/FileJson.h"
#include "../../BasePuzzle.h"
#include "NumberSprite.h"
#include <random>

// パネルの種類を定義するenumクラス
class Puzzle15 : public BasePuzzle {

public:
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
		bool isPlaced;           // 正しい位置に配置されたか
		Vector2 correctPosition; // 正しい位置
	};

	// バラバラに置くパネル用構造体
	struct ScatteredPanel {
		int number;     // パネルの番号（1～15）
		Sprite* sprite; // スプライト
		Vector2 pos;    // 初期位置（外周）
		bool isPlaced;  // 正しく配置されたか
	};
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

	// ランダムにバラバラパネル生成
	void CreateScatteredPieces();
	// 外周のランダム座標
	Vector2 GetRandomScatterPos();
	// ドロップ時の判定
	void TryPlacePiece(ScatteredPanel& piece, const Vector2& dropPos);

	// クリアチェック
	void CheckClear();

private:
	std::vector<ScatteredPanel> scatteredPieces_;
	ScatteredPanel* draggingPiece_ = nullptr;
	Vector2 dragOffset_; // ドラッグ時の位置補正
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

	// パネルのテクスチャ
	std::vector<uint32_t> panelTextures_;

	// Json読み書き用のファイルアクセサ
	FileJson::FileAccessor* fileAccessor_;
	// クリックされたパネルのインデックスを保持する変数
	int selectedSpriteIndex = -1;

	// 数字スプライト
	// std::vector<NumberSprite> numberSprite;

	// 正しい位置がわかりやすくするためのテクスチャ
	uint32_t correctPositionTexture_;
	// 正しい位置がわかりやすくするためのスプライト
	Sprite* correctPositionSprite;

	uint32_t flameTexture_;
	Sprite* flameSprite;

	// クリアフラグ
	bool isClear_;
	// ホールドしているか
	bool isHold_ = false;

	// 乱数シード
	std::mt19937 randomSeed;

	float scatterRadius_ = 500.0f; // パネルを配置する外周の半径
};