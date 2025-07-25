#pragma once 
#include "KamataEngine.h"

#include "EnemyActor.h"

using namespace KamataEngine;

class ActorManager;
class EnemyFactory;
class EnemyShort;

class EnemyManager
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">モデルの座標</param>
	void Initialize(Model* longModel, Model* shortModel, Model* flyModel, Model* bulletModel, const Vector3 pos, ActorManager* actorManager);

	/// <summary>
	/// アップデート
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera& camera);

	void RandomCreate();

	std::list<std::shared_ptr<EnemyActor>> GetEnemy(){ return Manager_; }
	
	void CreateEnemyLong();
	
	void CreateEnemyShort();

	void CreateEnemyFly();

private:
	Model* longModel_ = nullptr;
	Model* shortModel_ = nullptr;
	Model* flyModel_ = nullptr;
	Model* bulletModel_ = nullptr;
	Vector3 Startpos_;

	ActorManager* actorManager_;

	float test = 1.0f;

	std::list<std::shared_ptr<EnemyActor>> Manager_;
	EnemyFactory* factory_;
	
	float createTimer_ = 0.0f;
	static inline const float createCoolTime_ = 3.0f;

	static inline const int fluEnemy = 40;
	static inline const int longEnemy = 60;
	static inline const int shortEnemy = 100;

	
	
};