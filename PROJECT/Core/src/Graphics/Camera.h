#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



struct Transform;

class Camera
{
public:
    Camera();

    void UpdateMatrices(const Transform& transform, float aspectRatio);

    const glm::mat4& View() const;
    const glm::mat4& Projection() const;    

private:
    glm::mat4 m_view{ 1.0f };
    glm::mat4 m_projection{ 1.0f };

    float m_fov = 45.0f;
    float m_nearPlane = 0.1f;
    float m_farPlane = 100000000.0f;

    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
};