#include "PlayerMain.h"

PlayerMain::PlayerMain()
{
}

PlayerMain::~PlayerMain()
{
}

void PlayerMain::Move()
{
	if (Input::GetInstance()->PushKey(DIK_W) || Input::GetInstance()->PushKey(DIK_UP))
	{
		velocity .z += PlayerMoveSpeed;
	}
	if (Input::GetInstance()->PushKey(DIK_S) || Input::GetInstance()->PushKey(DIK_DOWN))
	{
		velocity .z -= PlayerMoveSpeed;
	}
	if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_LEFT))
	{
		velocity .x -= PlayerMoveSpeed;
	}
	if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		velocity .x += PlayerMoveSpeed;
	}
}

void PlayerMain::Attack()
{
}
