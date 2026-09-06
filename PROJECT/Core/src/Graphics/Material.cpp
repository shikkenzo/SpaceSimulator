#include "Material.h"

#include <stdexcept>



Material::Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
    : m_shader(std::move(shader)) , m_texture(std::move(texture))
{
}

void Material::Bind()
{
    if (!m_shader)
        throw std::runtime_error("Material::Bind(): material has no shader");

    if (!m_texture)
        throw std::runtime_error("Material::Bind(): material has no texture");

    m_shader->Bind();
    m_texture->Bind();
}
