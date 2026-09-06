#pragma once

#include <glad/glad.h>

#include <filesystem>



class Texture
{
public:
    GLuint ID = 0;

    Texture(const std::filesystem::path& image);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    void Bind() const;
    void Unbind() const;
    void Delete();
};
