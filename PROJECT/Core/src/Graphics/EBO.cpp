#include "EBO.h"



EBO::EBO(const std::vector<GLuint>& indices)
{
    glGenBuffers(1, &ID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(GLuint)), indices.data(), GL_STATIC_DRAW);
}

EBO::~EBO()
{
    Delete();
}

void EBO::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }
void EBO::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::Delete()
{
    if (ID)
    {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
}
