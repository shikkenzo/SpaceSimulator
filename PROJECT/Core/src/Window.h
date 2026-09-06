#pragma once



struct GLFWwindow;

class Window
{
public:
    int Init(int width, int height, const char* title);
    void Shutdown();

    void SwapBuffers();
    void PollEvents();
    bool ShouldClose() const;

public:
    int GetWidth() const;
    int GetHeight() const;
    float GetAspectRatio() const;

    GLFWwindow* GetNativeWindow() const;
private:
    GLFWwindow* m_window = nullptr;

    int m_width = 0;
    int m_height = 0;
};
