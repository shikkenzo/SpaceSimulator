#include "Input.h"

#include <algorithm>



GLFWwindow* Input::m_window = nullptr;
bool Input::m_keys[GLFW_KEY_LAST + 1]{};
bool Input::m_mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1]{};

void Input::Update(GLFWwindow* window)
{
    m_window = window;
    if (!m_window)
        return;

    for (int i = 0; i <= GLFW_KEY_LAST; ++i)
        m_keys[i] = glfwGetKey(m_window, i) == GLFW_PRESS;

    for (int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i)
        m_mouseButtons[i] = glfwGetMouseButton(m_window, i) == GLFW_PRESS;
}

bool Input::KeyDown(int key)
{
    return key >= 0 && key <= GLFW_KEY_LAST && m_keys[key];
}

bool Input::MouseButtonDown(int button)
{
    return button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST && m_mouseButtons[button];
}

void Input::GetMousePosition(double& x, double& y)
{
    x = y = 0.0;
    if (m_window)
        glfwGetCursorPos(m_window, &x, &y);
}

void Input::SetMousePosition(double x, double y)
{
    if (m_window)
        glfwSetCursorPos(m_window, x, y);
}

void Input::HideCursor()
{
    if (m_window)
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::ShowCursor()
{
    if (m_window)
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Input::GetScreenSize(int& width, int& height)
{
    width = height = 0;
    if (m_window)
        glfwGetFramebufferSize(m_window, &width, &height);
}
