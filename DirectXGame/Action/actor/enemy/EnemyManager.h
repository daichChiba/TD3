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
	void Initialize(Model* model, Model* bulletModel, const Vector3 pos, ActorManager* actorManager);

	/// <summary>
	/// アップデート
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera& camera);

	void CreateEnemyTest();

	void CreateEnemyShort();

	void CreateEnemyFly();

private:
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	Vector3 Startpos_;

	ActorManager* actorManager_;

	float test = 1.0f;

	std::list<std::shared_ptr<EnemyActor>> Manager_;
	EnemyFactory* factory_;
	
};