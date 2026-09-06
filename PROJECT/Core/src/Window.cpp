#include "Window.h"

#include <GLFW/glfw3.h>



int Window::Init(int width, int height, const char* title)
{
    if (width <= 0 || height <= 0 || !title)
        return -1;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!m_window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    return 0;
}

void Window::Shutdown()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
    m_width = 0;
    m_height = 0;
}

void Window::SwapBuffers()
{
    if (m_window)
        glfwSwapBuffers(m_window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return !m_window || glfwWindowShouldClose(m_window);
}

int Window::GetWidth() const { return m_width; }
int Window::GetHeight() const { return m_height; }

float Window::GetAspectRatio() const
{
    return m_height > 0 ? static_cast<float>(m_width) / static_cast<float>(m_height) : 1.0f;
}

GLFWwindow* Window::GetNativeWindow() const { return m_window; }
