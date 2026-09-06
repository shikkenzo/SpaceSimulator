#pragma once

#include "Scene.h"
#include "Graphics/Renderer.h"


class Application
{
public:
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Shutdown() = 0;

    void Render(Renderer& renderer, float aspectRatio)
    {
        renderer.Render(m_scene, aspectRatio);
    }

protected:
    Scene m_scene;
};
