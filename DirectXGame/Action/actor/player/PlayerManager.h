#pragma once 
#include "KamataEngine.h"

#include "PlayerActor.h"

using namespace KamataEngine;

class ActorManager;
class PlayerFactory;

class PlayerManager
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

	PlayerActor* GetPlayer() { return Plauyer_.get();}

	void CreatePlayerMain();

private:
	Model* model_;
	Model* bulletModel_;
	Vector3 Startpos_;

	ActorManager* actorManager_;

	std::unique_ptr<PlayerActor> Plauyer_;
	PlayerFactory* factory_;
};