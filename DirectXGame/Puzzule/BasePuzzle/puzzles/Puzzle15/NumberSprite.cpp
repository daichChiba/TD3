#include "NumberSprite.h"
using namespace MathUtility;

// 初期化処理
void NumberSprite::Initialize(Vector2 pos, float size, const Center centor) {
	pos_ = pos;       // 位置をメンバ変数にコピー
	size_ = size;     // サイズをメンバ変数にコピー
	centor_ = centor; // 中心点をメンバ変数にコピー
}

// 描画処理
void NumberSprite::Draw() {
	// 保持している全てのSpriteを描画する
	for (Sprite s : sprite) {
		s.Draw(); // 各Spriteの描画処理を呼び出す
	}
}

// 表示する数値を設定する処理
void NumberSprite::SetNumber(int num) {
	bool is = false; // 負の数かどうかを判定するフラグ

	// 数値が負の数であるかを判定
	if (num < 0) {
		is = true; // 負の数であればフラグを立てる
	}

	sprite.clear(); // 既存のSpriteをクリアする

	// 絶対値を求める。ゼロ以下なら絶対値化。
	int index = num <= 0 ? -num : num;

	// 数値からSpriteを生成する
	Number(index);

	// 中心点の設定に応じて位置を調整する
	switch (centor_) {
	case Center::Left:
		// 左寄せの場合は何もしない
		break;
	case Center::Central:
		// 中央寄せの場合
		for (int i = 0; i < sprite.size(); i++) {
			// 各Spriteの位置を計算する
			Vector2 pos = {pos_.x - ((cSize.x * size_) * ((sprite.size() - 1) / 2.0f - i)), pos_.y}; // 中心から左右にずらす量を計算

			// Spriteの位置を設定する
			sprite[i].SetPosition(pos);

			// 負の数の場合は色を変更する
			if (is) {
				sprite[i].SetColor({1.0f, 0.0f, 0.0f, 1.0f}); // 赤色にする
			}
		}
		break;
	case Center::Right:
		// 右寄せの場合は何もしない
		break;
	}
}

// 数値からSpriteを生成する再帰関数
int NumberSprite::Number(int num, int num2) {
	int i = num;
	// 再帰処理で各桁の数字を取り出す
	if (num >= num2 * 10) {
		// 次の桁を処理する
		i = Number(num, num2 * 10);
		i = i / num2; // 整数除算で桁の値を抽出
	} else {
		// 最上位桁の場合
		i = num / num2; // 整数除算で桁の値を抽出
	}

	// Spriteを生成して追加する
	sprite.push_back(CreateSprite(i));

	// 残りの桁を返す
	return num % num2; // 剰余を返す
}

// 数値に対応するSpriteを生成する
Sprite NumberSprite::CreateSprite(int num) {
	Sprite s;
	s.Initialize(); // Spriteの初期化

	// テクスチャをロードする
	TH = TextureManager::GetInstance()->Load("Puzzle15/number.png");
	s.SetTextureHandle(TH);                         // テクスチャハンドルを設定
	s.SetAnchorPoint({0.5f, 0.5f});                 // アンカーポイントを設定（中心）
	s.SetSize(cSize * size_);                       // サイズを設定
	s.SetTextureRect({cSize.x * num, 0.0f}, cSize); // テクスチャの矩形範囲を設定（数字に対応する部分）
	return s;                                       // 生成したSpriteを返す
}