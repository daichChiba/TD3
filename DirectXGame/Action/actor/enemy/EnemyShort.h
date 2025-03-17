#pragma once

#include "KamataEngine.h"
using namespace KamataEngine;
#include "EnemyActor.h"

// 歩く近距離攻撃する敵
class EnemyShort : public EnemyActor {
public:
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

};
