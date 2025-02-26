#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class FollowCamera
{
public:
	void Initialize();

	void Update();

	void SetTarget( const WorldTransform* target){ target_ = target; }
private:
	Camera* followCamera;
	const WorldTransform* target_ = nullptr;
};

