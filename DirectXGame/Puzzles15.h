#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include <vector>


class Puzzles15 {
public:
	Puzzles15();
	~Puzzles15();

	void Initialize();
	void Update();
	void Draw();

private:
	Sprite* puzzles_ = nullptr;
	uint32_t puzzles15_ = 0;
	// ワールド変換データ
	WorldTransform worldTransform_;

	// ビュープロジェクション
	Camera camera_;

	WorldTransform worldTransformFont_;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

};
