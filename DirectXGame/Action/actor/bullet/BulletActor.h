#pragma once

#include "KamataEngine.h"

using namespace KamataEngine;

enum class BulletType {
	player,
	enemy,
};

class ActorManager;

class BulletActor
{
public:
	void Initialize(Model* model, Vector3 pos);
	void Update();
	virtual void Draw(Camera& camera);

	void SetScale( Vector3 scale){ worldTransform_.scale_ = scale; }
	void SetMove( Vector3 MoveVectorl){ move_ = MoveVectorl; }
	
	bool IsDelete() const { return isDelete_; }
	virtual void OnCollision();
	Vector3 GetWorldPosition(){ return worldTransform_.translation_; }
	float GetRadius() { return radius_; }

	int GetDamage(){ return damage_;}

	BulletType GetBulletType() {return bullet_; }

	void SetEnumClassEnemy() { bullet_ = BulletType::enemy; }
	void SetEnumClassPlayer() { bullet_ = BulletType::player; }

	/// <summary>
	/// SetActorManger
	/// </summary>
	void SetACManager(ActorManager* acManager);
protected:
	virtual void Move();
	virtual void Attack(){ return;};
	virtual void DeleteTimerCheck();

	Model* model_ = nullptr;
	WorldTransform worldTransform_;

	/// <summary>
	/// actorManger
	/// </summary>
	/// 使うときはSetしなければならない
	ActorManager* actorManager_;

	Vector3 move_;
	
	bool isDelete_ = false;
	float deleteTimer_;
	static inline const float kDeleteDefaltTime_ = 5.0f;

	float radius_ = 1.0f;
	int damage_ = 1; 

	ObjectColor* color = nullptr;

	BulletType bullet_ = BulletType::player;
};