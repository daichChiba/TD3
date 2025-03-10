#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class FollowCamera
{
public:
	void Initialize();

	void Update();



	void DrawImgui();

	void DrowImgui();

	const Camera&  GetCamera(){ return followCamera;}

	void SetTarget( const WorldTransform* target){ target_ = target; }
private:

	XINPUT_STATE xinput_;
	XINPUT_STATE preXinput_;

	Camera followCamera;
	const WorldTransform* target_ = nullptr;

	float Rx;
	float Ry;

	bool moveCameraRotateXAdd;
	bool moveCameraRotateXLower;

	Vector3 offset_ = {0.0f, 2.0f, -10.0f};

	static inline const float kRotationSpeed = 0.008f;

	static inline const float kTranslationSpeed = 0.005f;

	static inline const float kDeadZone = 0.1f;

	static inline const float kMinCameraHeight = 0.5f;
	static inline const float kMaxCameraHeight = 7.0f;
};

