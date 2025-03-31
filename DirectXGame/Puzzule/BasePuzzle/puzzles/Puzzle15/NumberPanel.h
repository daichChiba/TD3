#pragma once
#include <KamataEngine.h>
#include <vector>
using namespace KamataEngine;

class NumberPanel {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 pos, int number, float size = 1.0f);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// 位置を設定する
	void SetPos(Vector2 pos) { pos_ = pos; }

	// 数字を設定する
	void SetNumber(int number) { number_ = number; }

	// 位置を取得する
	Vector2 GetPos() const { return pos_; }

private:
	// Spriteを生成する

	Sprite CreateSprite(int number);

private:
	// Sprite
	Sprite sprite;

	// テクスチャハンドル
	uint32_t TH;

	// 位置
	Vector2 pos_;

	// サイズ
	float size_;

	// 　表示する数字
	int number_;

	// 各数字のSpriteのサイズ(固定値)
	const Vector2 cSize = {64.0f, 64.0f};
};