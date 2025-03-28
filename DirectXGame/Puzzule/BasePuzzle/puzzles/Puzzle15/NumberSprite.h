#pragma once
#include <KamataEngine.h>
#include <vector>
using namespace KamataEngine;

// 中心点の種類を定義するenumクラス
enum class Center {
	Left,    // 左寄せ
	Central, // 中央寄せ
	Right,   // 右寄せ
};

// 数字のスプライトを扱うクラス
class NumberSprite {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 pos, float size = 1.0f, const Center centor = Center::Central);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// 位置を設定する
	void SetPos(Vector2 pos) { pos_ = pos; }

	// 表示する数値を設定する
	void SetNumber(int num);

	// 位置を取得する
	Vector2 GetPos() const { return pos_; }

private:
	// 数値からSpriteを生成する再帰関数
	int Number(int num, int num2 = 1);

	// 数値に対応するSpriteを生成する
	Sprite CreateSprite(int num);

private:
	// 中心点の種類
	Center centor_;

	// Spriteの配列
	std::vector<Sprite> sprite;

	// テクスチャハンドル
	uint32_t TH;

	// 位置
	Vector2 pos_;

	// サイズ
	float size_;

	// 各数字のSpriteのサイズ(固定値)
	const Vector2 cSize = {40.0f, 64.0f};
};