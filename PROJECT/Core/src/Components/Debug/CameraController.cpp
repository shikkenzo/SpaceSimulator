#include "CameraController.h"

#include "Components/TransformComponent.h"
#include "Object.h"
#include "Debug/Input.h"

#include <glm/gtx/vector_angle.hpp>



FreeCameraController::FreeCameraController(float speed, float sensitivity)
	: m_speed(speed), m_sensitivity(sensitivity)
{
}

void FreeCameraController::Update(float deltaTime, Object& object)
{
	Transform& transform = object.RequireComponent<TransformComponent>().transform();

	UpdateKeyboard(transform, deltaTime);

	UpdateMouse(transform);
}

void FreeCameraController::UpdateKeyboard(Transform& transform, float deltaTime)
{
	glm::vec3 forward = GetForward(transform);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 right = GetRight(transform);

	float speed = m_speed * deltaTime;

	if (Input::KeyDown(GLFW_KEY_LEFT_SHIFT))
		speed *= 2.5f;

	if (Input::KeyDown(GLFW_KEY_W))
		transform.m_position += speed * forward;

	if (Input::KeyDown(GLFW_KEY_A))
		transform.m_position -= speed * right;

	if (Input::KeyDown(GLFW_KEY_S))
		transform.m_position -= speed * forward;

	if (Input::KeyDown(GLFW_KEY_D))
		transform.m_position += speed * right;

	if (Input::KeyDown(GLFW_KEY_E))
		transform.m_position += speed * up;

	if (Input::KeyDown(GLFW_KEY_Q))
		transform.m_position -= speed * up;
}

void FreeCameraController::UpdateMouse(Transform& transform)
{
	int width;
	int height;

	Input::GetScreenSize(width, height);

	if (!Input::MouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		Input::ShowCursor();
		m_firstClick = true;
		return;
	}

	Input::HideCursor();

	const int centerX = width / 2;
	const int centerY = height / 2;

	if (m_firstClick)
	{
		Input::SetMousePosition(centerX, centerY);
		m_firstClick = false;
	}

	double mouseX;
	double mouseY;

	Input::GetMousePosition(mouseX, mouseY);

	float rotX = m_sensitivity * static_cast<float>(mouseY - centerY) / static_cast<float>(height);

	float rotY = m_sensitivity * static_cast<float>(mouseX - centerX) / static_cast<float>(width);

	glm::vec3 forward = GetForward(transform);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 right = GetRight(transform);

	// Pitch
	glm::quat pitch = glm::angleAxis(glm::radians(-rotX), right);

	glm::vec3 newForward = glm::normalize(pitch * forward);

	const float minAngle = glm::radians(5.0f);

	if (glm::angle(newForward, up) > minAngle && glm::angle(newForward, -up) > minAngle)
	{
		transform.m_rotation = glm::normalize(pitch * transform.m_rotation);
	}

	// Yaw
	glm::quat yaw = glm::angleAxis(glm::radians(-rotY), up);

	transform.m_rotation = glm::normalize(yaw * transform.m_rotation);

	Input::SetMousePosition(centerX, centerY);
}

glm::vec3 FreeCameraController::GetForward(const Transform& transform) const
{
	return glm::normalize(transform.m_rotation * glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 FreeCameraController::GetRight(const Transform& transform) const
{
	const glm::vec3 forward = GetForward(transform);
	const glm::vec3 up(0.0f, 1.0f, 0.0f);

	return glm::normalize(glm::cross(forward, up));
}
