#pragma once
#include <vector>
#include <KamataEngine.h>
using namespace KamataEngine;
// 数字の中心
enum class Center {
	Left,
	Central,
	Right,
};

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

	/// <summary>
	/// 数字の設定
	/// </summary>
	/// <param name="num"></param>
	void SetNumber(int num);

private:
	/// <summary>
	/// スプライトの生成
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	Sprite CreateSprite(int num);

private:
	// 中心
	Center centor_;
	// スプライト
	std::vector<Sprite> sprite;
	// テクスチャ
	uint32_t TH;

	Vector2 pos_;
	float size_;
	// 数字のサイズ
	const Vector2 cSize = {32.0f, 64.0f};
};
