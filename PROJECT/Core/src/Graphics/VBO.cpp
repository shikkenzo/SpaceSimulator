#include "VBO.h"



VBO::VBO(const std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &ID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);
}

VBO::~VBO()
{
    Delete();
}

void VBO::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, ID); }
void VBO::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::Delete()
{
    if (ID)
    {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
}
