#include "NumberSprite.h"
using namespace MathUtility;
void NumberSprite::Initialize(Vector2 pos, float size, const Center centor) {
	pos_ = pos;
	size_ = size;
	centor_ = centor;
}

void NumberSprite::Draw() {
	// spriteの描画
	for (Sprite sprite_ : sprite) {
		sprite_.Draw();
	}
}

void NumberSprite::SetNumber(int num) {
	// 数字の設定
	bool is = false;
	// 負の数か？
	if (num < 0) {
		is = true;
	}

	// 絶対値を取得
	int index = num <= 0 ? -num : num;
	// 100の位
	int index2 = 0;
	// スプライトのクリア
	sprite.clear();
	// 100の位があるか？
	if (index >= 100) {
		index2 = index / 100;
		index = index % 100;
		sprite.push_back(CreateSprite(index2));
	}
	// 10の位があるか？
	if (index >= 10) {
		index2 = index / 10;
		index = index % 10;
		sprite.push_back(CreateSprite(index2));
	}
	// 1の位
	index2 = index;
	// スプライトの追加
	sprite.push_back(CreateSprite(index2));

	switch (centor_) {
		// 左揃え
	case Center::Left:
		break;
		// 中央揃え
	case Center::Central:
		for (int i = 0; i < sprite.size(); i++) {
			Vector2 pos = {pos_.x - ((cSize.x * size_) * ((sprite.size() - 1) / 2.0f - i)), pos_.y};
			sprite[i].SetPosition(pos);
			if (is) {
				sprite[i].SetColor({1.0f, 0.0f, 0.0f, 1.0f});
			}
		}
		break;
		// 右揃え
	case Center::Right:
		break;
	}
}

Sprite NumberSprite::CreateSprite(int num) {
	Sprite sprite_;
	sprite_.Initialize();

	TH = TextureManager::GetInstance()->Load("../../../../Resources/Puzzle15/number.png");
	sprite_.SetTextureHandle(TH);
	sprite_.SetAnchorPoint({0.5f, 0.5f});
	sprite_.SetSize(cSize * size_);
	sprite_.SetTextureRect({cSize.x * num, 0.0f}, cSize);
	return sprite_;
}
