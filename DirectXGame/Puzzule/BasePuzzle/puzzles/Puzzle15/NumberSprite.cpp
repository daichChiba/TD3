#include "NumberSprite.h"
using namespace MathUtility;
void NumberSprite::Initialize(Vector2 pos, float size, const Center centor) {
	pos_ = pos;
	size_ = size;
	centor_ = centor;
}

void NumberSprite::Draw() {
	for (Sprite s : sprite) {
		s.Draw();
	}
}

void NumberSprite::SetNumber(int num) {
	bool is = false;
	if (num < 0) {
		is = true;
	}


	int index = num <= 0 ? -num : num;
	int index2 = 0;
	sprite.clear();
	if (index >= 100) {
		index2 = index / 100;
		index = index % 100;
		sprite.push_back(CreateSprite(index2));
	}
	if (index >= 10) {
		index2 = index / 10;
		index = index % 10;
		sprite.push_back(CreateSprite(index2));
	}
	index2 = index;
	sprite.push_back(CreateSprite(index2));

	switch (centor_) {
	case Center::Left:

		break;
	case Center::Central:
		for (int i = 0; i < sprite.size(); i++) {
			Vector2 pos = {pos_.x - ((cSize.x * size_) * ((sprite.size() - 1) / 2.0f - i)), pos_.y};
			sprite[i].SetPosition(pos);
			if (is) {
				sprite[i].SetColor({1.0f, 0.0f, 0.0f, 1.0f});
			}
		}
		break;
	case Center::Right:
		break;
	}
	
}

Sprite NumberSprite::CreateSprite(int num) {
	Sprite s;
	s.Initialize();

	TH = TextureManager::GetInstance()->Load("number.png");
	s.SetTextureHandle(TH);
	s.SetAnchorPoint({0.5f, 0.5f});
	s.SetSize(cSize * size_);
	s.SetTextureRect({cSize.x * num, 0.0f}, cSize);
	return s;
}
