#pragma once

#include "Graphics/VBO.h"
#include "Graphics/VAO.h"
#include "Graphics/EBO.h"

#include <glad/glad.h>

#include <cstdint>
#include <vector>



class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
    void Draw() const;

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    VAO m_vertexArray;
    VBO m_vertexBuffer;
    EBO m_elementBuffer;
};
