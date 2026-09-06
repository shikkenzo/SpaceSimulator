#pragma once

#include "Components/Component.h"

#include <glm/glm.hpp>



struct Object;
struct Transform;

class FreeCameraController : public ComponentImpl<FreeCameraController>
{
public:
	FreeCameraController(float speed = 100.0f, float sensitivity = 100.0f);

	void Update(float deltaTIme, Object& object) override;

private:
	void UpdateKeyboard(Transform& transform, float deltaTime);

	void UpdateMouse(Transform& transform);

	glm::vec3 GetForward(const Transform& transform) const;

	glm::vec3 GetRight(const Transform& transform) const;

private:
	float m_speed;
	float m_sensitivity;

	bool m_firstClick = true;
};
