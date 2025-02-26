#include "PlayerManager.h"

#include "PlayerFactory.h"

#include "PlayerMain.h"

void PlayerManager::Initialize(Model* model, Model* bulletModel, const Vector3 pos)
{
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;
	bulletModel_ = bulletModel;

	Startpos_ = pos;

	factory_ = new PlayerFactory();
}

void PlayerManager::Update()
{
	Manager_->Update();
}

void PlayerManager::Draw(Camera& camera)
{
	Manager_->Draw(camera);
}

void PlayerManager::CreatePlayerMain()
{
	Manager_ = std::make_unique<PlayerMain>();
	Manager_->Initialize(model_, bulletModel_, Startpos_);
}
