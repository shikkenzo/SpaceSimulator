#pragma once

#include "Graphics/ShaderClass.h"
#include "Graphics/Texture.h"

#include <vector>
#include <memory>



class Material
{
public:
    Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

    void Bind();

public:
    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<Texture> m_texture;
};
