#include "NumberPanel.h"
using namespace MathUtility;

// 初期化処理
void NumberPanel::Initialize(Vector2 pos, int number, float size) {
	// 位置をメンバ変数にコピー
	pos_ = pos;
	// サイズをメンバ変数にコピー
	size_ = size;
	// 表示する数字をメンバ変数にコピー
	number_ = number;

	sprite = CreateSprite(number);
	sprite.SetPosition(pos);
}

// 描画処理
void NumberPanel::Draw() {
	sprite.Draw(); // Spriteの描画処理を呼び出す
}

// 数値に対応するSpriteを生成する
Sprite NumberPanel::CreateSprite(int number) {
	Sprite s;
	s.Initialize(); // Spriteの初期化

	// テクスチャをロードする
	TH = TextureManager::GetInstance()->Load("Puzzle15/puzzle15-sheet.png");
	// テクスチャハンドルを設定
	s.SetTextureHandle(TH);
	// アンカーポイントを設定（中心）
	s.SetAnchorPoint({ 0.5f, 0.5f });
	// サイズを設定
	s.SetSize(cSize * size_);
	// テクスチャの矩形範囲を設定（数字に対応する部分）
	s.SetTextureRect({ cSize.x * number, 0.0f }, cSize);
	// 生成したSpriteを返す
	return s;
}