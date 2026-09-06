#pragma once

#include <GLFW/glfw3.h>



class Input
{
public:
    static void Update(GLFWwindow* window);

    static bool KeyDown(int key);

    static bool MouseButtonDown(int button);

    static void GetMousePosition(double& x, double& y);

    static void SetMousePosition(double x, double y);

    static void HideCursor();

    static void ShowCursor();

    static void GetScreenSize(int& width, int& height);

private:
    static GLFWwindow* m_window;

    static bool m_keys[GLFW_KEY_LAST + 1];
    static bool m_mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
};