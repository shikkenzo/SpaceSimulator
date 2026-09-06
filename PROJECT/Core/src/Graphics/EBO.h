#pragma once

#include <glad/glad.h>
#include <vector>



class EBO
{
public:
    EBO() = default;
    explicit EBO(const std::vector<GLuint>& indices);
    ~EBO();

    EBO(const EBO&) = delete;
    EBO& operator=(const EBO&) = delete;

    void Bind() const;
    void Unbind() const;
    void Delete();

private:
    GLuint ID = 0;
};
