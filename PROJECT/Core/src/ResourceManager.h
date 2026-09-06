#pragma once

#include "Graphics/ShaderClass.h"
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"

#include <memory>
#include <string>
#include <filesystem>
#include <unordered_map>



class ResourceManager
{
public:
	static std::shared_ptr<Shader> LoadShader(const std::filesystem::path& vertex, const std::filesystem::path& fragment);

	static std::shared_ptr<Texture> LoadTexture(const std::filesystem::path& image);

	static std::shared_ptr<Material> RegisterMaterial(const std::string& name, std::shared_ptr<Material> material);

	static std::shared_ptr<Material> GetMaterial(const std::string& name);

	static std::shared_ptr<Mesh> RegisterMesh(const std::string& name, std::shared_ptr<Mesh> mesh);

	static std::shared_ptr<Mesh> GetMesh(const std::string& name);

	static void Clear();

private:
	static std::unordered_map<std::string, std::weak_ptr<Shader>> m_shaders;
	static std::unordered_map<std::string, std::weak_ptr<Texture>> m_textures;
	static std::unordered_map<std::string, std::weak_ptr<Material>> m_materials;
	static std::unordered_map<std::string, std::weak_ptr<Mesh>> m_meshes;
};
