#pragma once

#include "KamataEngine.h"
using namespace KamataEngine;
#include "EnemyActor.h"
#include "random"

// 飛行する敵
class EnemyFly : public EnemyActor {
public :

	EnemyFly();
	~EnemyFly();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

private:
	/// <summary>
	/// 動き
	/// </summary>
	void Move() override;

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack() override;

	//ランダム
	std::mt19937 random_;
	std::uniform_real_distribution<float> randomDist_;
	float moveTimer_;
	//ランダムな動きを生成する感覚(秒)
	static constexpr float kMoveInterval_ = 1.0f;

};
