#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <vector>



struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

class VBO
{
public:
    VBO() = default;
    explicit VBO(const std::vector<Vertex>& vertices);
    ~VBO();

    VBO(const VBO&) = delete;
    VBO& operator=(const VBO&) = delete;

    void Bind() const;
    void Unbind() const;
    void Delete();

private:
    GLuint ID = 0;
};
