#pragma once

#include "KamataEngine.h"
using namespace KamataEngine;
#include "EnemyActor.h"

// 飛行する敵
class EnemyFly : public EnemyActor {
public :

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
