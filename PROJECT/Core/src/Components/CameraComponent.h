#pragma once

#include "Component.h"
#include "Graphics/Camera.h"



struct CameraComponent : public ComponentImpl<CameraComponent>
{
	const Camera& GetCamera() const { return m_camera; }
	Camera& camera() { return m_camera; }

private:
	Camera m_camera;
};

