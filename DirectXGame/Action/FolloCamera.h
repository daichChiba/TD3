#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class FollowCamera
{
public:
	void Initialize();

	void Update();

	void DrowImgui();

	const Camera&  GetCamera(){ return followCamera;}

	void SetTarget( const WorldTransform* target){ target_ = target; }
private:

	XINPUT_STATE xinput_;
	XINPUT_STATE preXinput_;

	Camera followCamera;
	const WorldTransform* target_ = nullptr;

	static inline const float kRotationSpeed = 0.01f;
	static inline const float targetDistance = 1.0f;
};

