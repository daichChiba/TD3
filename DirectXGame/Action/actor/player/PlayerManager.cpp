#include "PlayerManager.h"

#include "../ActorManager.h"

#include "PlayerFactory.h"
#include "PlayerMain.h"

void PlayerManager::Initialize(Model* model, Model* bulletModel, const Vector3 pos, ActorManager* actorManager)
{
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;
	bulletModel_ = bulletModel;

	Startpos_ = pos;

	actorManager_ = actorManager;

	factory_ = new PlayerFactory();
}

void PlayerManager::Update()
{
	Plauyer_->Update();
}

void PlayerManager::Draw(Camera& camera)
{
	Plauyer_->Draw(camera);
}

void PlayerManager::CreatePlayerMain()
{
	Plauyer_ = factory_->CreatePlayer();
	Plauyer_->Initialize(model_, bulletModel_, Startpos_, actorManager_);
}
