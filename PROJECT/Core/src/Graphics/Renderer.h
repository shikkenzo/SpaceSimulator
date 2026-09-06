#pragma once



class Scene;

class Renderer
{
public:
    void Init();
    void Render(const Scene& scene, float aspectRatio);
    void Shutdown();

    void SetViewportSize(int width, int height);

    void Clear();
private:
    int m_width = 0;
    int m_height = 0;
};
