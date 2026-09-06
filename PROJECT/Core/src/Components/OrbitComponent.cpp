#include "Components/OrbitComponent.h"

#include "Object.h"
#include "Components/TransformComponent.h"

#include <glm/gtc/constants.hpp>

#include <cmath>
#include <stdexcept>



OrbitComponent::OrbitComponent(Transform& attractor)
    : attractorTransform(attractor)
{
}

void OrbitComponent::Update(float deltaTime, Object& object)
{
    float tolerance = 0.0001;

    auto& transformComponent = object.RequireComponent<TransformComponent>();

    const float axisLengthSquared = glm::dot(orbitAxis, orbitAxis);

    if (axisLengthSquared <= tolerance)
        throw std::runtime_error("OrbitComponent::Update(): orbitAxis must not be zero");

    const glm::vec3 axis = orbitAxis / std::sqrt(axisLengthSquared);

    glm::vec3 perpendicular;

    if (std::abs(axis.x) > tolerance || std::abs(axis.z) > tolerance)
    {
        perpendicular = glm::normalize(glm::vec3(-axis.z, 0.0f, axis.x));
    }
    else
    {
        perpendicular = glm::vec3(1.0f, 0.0f, 0.0f);
    }

    const glm::vec3 perpendicular2 = glm::normalize(glm::cross(axis, perpendicular));

    currentAngle = std::fmod(currentAngle + glm::radians(angularSpeed) * deltaTime, glm::two_pi<float>());

    const glm::vec3 newRelativePosition = perpendicular * std::cos(currentAngle + startingAngle) * radius + perpendicular2 * std::sin(currentAngle + startingAngle) * radius;

    transformComponent.localPosition() = attractorTransform.m_position + newRelativePosition;
}
