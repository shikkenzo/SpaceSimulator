#pragma once

#include "Graphics/VBO.h"

#include <glad/glad.h>



class VAO
{
public:
    VAO();
    ~VAO();

    VAO(const VAO&) = delete;
    VAO& operator=(const VAO&) = delete;

    void LinkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, std::size_t offset) const;

    void Bind() const;
    void Unbind() const;
    void Delete();

private:
    GLuint ID = 0;
};
