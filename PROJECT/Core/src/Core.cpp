#include "Core.h"

#include "Debug/Input.h"

#include <algorithm>
#include <stdexcept>



void Core::Init()
{
    if (m_window.Init(1920, 1080, "WINDOW") != 0)
        throw std::runtime_error("Core::Init(): failed to create window");

    m_renderer.Init();
}

void Core::Shutdown()
{
    m_renderer.Shutdown();
    m_window.Shutdown();
}

void Core::Run(Application& app)
{
    app.Init();

    m_lastFrameTime = std::chrono::steady_clock::now();

    while (!m_window.ShouldClose())
    {
        Input::Update(m_window.GetNativeWindow());

        const auto now = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(now - m_lastFrameTime).count();
        m_lastFrameTime = now;

        deltaTime = std::clamp(deltaTime, 0.0f, 0.1f);

        app.Update(deltaTime);

        m_renderer.Clear();
       
        app.Render(m_renderer, m_window.GetAspectRatio());

        m_window.SwapBuffers();
        m_window.PollEvents();
    }

    app.Shutdown();
}
