#pragma once

#include "Window.h"
#include "Application.h"
#include "Graphics/Renderer.h"

#include <chrono>



class Core
{
public:
    void Init();
    void Run(Application& app);
    void Shutdown();

private:
    Window m_window;
    Renderer m_renderer;

private:
    std::chrono::time_point<std::chrono::steady_clock> m_lastFrameTime;
};
