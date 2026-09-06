#include "VAO.h"



VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
    Delete();
}

void VAO::LinkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, std::size_t offset) const
{
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, reinterpret_cast<const void*>(offset));
    glEnableVertexAttribArray(layout);
}

void VAO::Bind() const { glBindVertexArray(ID); }
void VAO::Unbind() const { glBindVertexArray(0); }

void VAO::Delete()
{
    if (ID)
    {
        glDeleteVertexArrays(1, &ID);
        ID = 0;
    }
}
