#pragma once

#include "Components/Component.h"

#include <glm/glm.hpp>



struct Transform;

struct OrbitComponent : public ComponentImpl<OrbitComponent>
{
	OrbitComponent(Transform& attractor);

	Transform& attractorTransform;
	float startingAngle = 0.0f; // degrees
	float angularSpeed = 1.0f;  // degrees
	float radius = 100.0f;

	glm::vec3 orbitAxis = glm::vec3(0.0f, 1.0f, 0.0f);

	void Update(float deltaTime, Object& object) override;

private:
	float currentAngle = 0.0f;
};
