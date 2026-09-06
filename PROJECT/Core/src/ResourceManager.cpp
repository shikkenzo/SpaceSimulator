#include "ResourceManager.h"



std::unordered_map<std::string, std::weak_ptr<Shader>> ResourceManager::m_shaders;

std::unordered_map<std::string, std::weak_ptr<Texture>> ResourceManager::m_textures;

std::unordered_map<std::string, std::weak_ptr<Material>> ResourceManager::m_materials;

std::unordered_map<std::string, std::weak_ptr<Mesh>> ResourceManager::m_meshes;



std::shared_ptr<Shader> ResourceManager::LoadShader(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
{
    std::string key = vertex.string() + "|" + fragment.string();

    auto it = m_shaders.find(key);

    if (it != m_shaders.end())
    {
        if (auto shader = it->second.lock())
            return shader;
    }

    const std::string vertexPath = vertex.string();
    const std::string fragmentPath = fragment.string();

    auto shader = std::make_shared<Shader>(vertexPath.c_str(), fragmentPath.c_str());

    m_shaders[key] = shader;

    return shader;
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::filesystem::path& image)
{
    const std::string key = image.string();

    auto it = m_textures.find(key);

    if (it != m_textures.end())
    {
        if (auto texture = it->second.lock())
            return texture;
    }

    auto texture = std::make_shared<Texture>(image.c_str());

    m_textures[key] = texture;

    return texture;
}

std::shared_ptr<Material> ResourceManager::RegisterMaterial(const std::string& name, std::shared_ptr<Material> material)
{
    auto it = m_materials.find(name);

    if (it != m_materials.end())
    {
        if (auto existing = it->second.lock())
            return existing;
    }

    m_materials[name] = material;

    return material;
}
std::shared_ptr<Material> ResourceManager::GetMaterial(const std::string& name)
{
    auto it = m_materials.find(name);

    if (it == m_materials.end())
        throw std::runtime_error("ResourceManager::GetMaterial(): material '" + name + "' is not registered.");

    if (auto material = it->second.lock())
        return material;

    m_materials.erase(it);

    throw std::runtime_error("ResourceManager::GetMaterial(): material '" + name + "' has expired");
}

std::shared_ptr<Mesh> ResourceManager::RegisterMesh(const std::string& name, std::shared_ptr<Mesh> mesh)
{
    auto it = m_meshes.find(name);

    if (it != m_meshes.end())
    {
        if (auto existing = it->second.lock())
            return existing;
    }

    m_meshes[name] = mesh;

    return mesh;
}
std::shared_ptr<Mesh> ResourceManager::GetMesh(const std::string& name)
{
    auto it = m_meshes.find(name);

    if (it == m_meshes.end())
        throw std::runtime_error("ResourceManager::GetMesh(): mesh '" + name + "' is not registered");

    if (auto mesh = it->second.lock())
        return mesh;

    m_meshes.erase(it);

    throw std::runtime_error("ResourceManager::GetMesh(): mesh '" + name + "' has expired");
}

void ResourceManager::Clear()
{
    m_shaders.clear();
    m_textures.clear();
    m_meshes.clear();
    m_materials.clear();
}
