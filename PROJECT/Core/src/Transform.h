#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>



struct Transform
{
    glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };
    glm::quat m_rotation = glm::identity<glm::quat>();
    glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };
};
