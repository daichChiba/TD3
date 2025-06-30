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

	

private:
	/// <summary>
	/// 動き
	/// </summary>
	void Move() override;

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack() override;

	/// <summary>
	/// プレイヤーに接近する
	/// </summary>
	void ApproachPlayer() override;
	
	float attackTiemr= 1.0f;
	static inline const float kAttackTiem= 3.0f;
	static inline const float kFlameTime = 1.0f / 60.0f;

};
