#include "FolloCamera.h"

void FollowCamera::Initialize()
{
	followCamera = new Camera();
	followCamera->Initialize();
}

void FollowCamera::Update()
{
	if (target_) {
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		followCamera
	}

	followCamera->UpdateMatrix();
}
