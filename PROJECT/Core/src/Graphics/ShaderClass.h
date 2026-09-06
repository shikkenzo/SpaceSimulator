#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>



std::string get_file_contents(const char* filename);

class Shader
{
public:
    GLuint ID = 0;

    Shader(const char* vertexFile, const char* fragmentFile);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void Bind() const;
    void Delete();

    GLint GetUniformLocationChecked(const char* name) const;
    void SetMat4(const char* name, const glm::mat4& value) const;

private:
    static bool CheckCompileErrors(GLuint object, bool program, const char* label);
};
