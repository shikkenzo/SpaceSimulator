#include "Camera.h"

#include "Transform.h"

#include <stdexcept>



Camera::Camera()
    : m_view(1.0f), m_projection(1.0f)
{
}

void Camera::UpdateMatrices(const Transform& transform, float aspectRatio)
{
    if (aspectRatio <= 0.0f)
        throw std::invalid_argument("Camera::UpdateMatrices(): aspect ratio must be positive");

    const glm::vec3 forward = glm::normalize(transform.m_rotation * glm::vec3(0.0f, 0.0f, -1.0f));

    const glm::vec3 up = glm::normalize(transform.m_rotation * m_up);

    m_view = glm::lookAt(transform.m_position, transform.m_position + forward, up);

    m_projection = glm::perspective(glm::radians(m_fov), aspectRatio, m_nearPlane, m_farPlane);
}

const glm::mat4& Camera::View() const { return m_view; }
const glm::mat4& Camera::Projection() const { return m_projection; }
