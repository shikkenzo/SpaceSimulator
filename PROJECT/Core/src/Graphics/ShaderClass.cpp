#include "ShaderClass.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <format>
#include <string>



std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in)
		throw std::runtime_error(std::string("get_file_contents(): failed to open shader file: ") + filename);

	std::ostringstream contents;
	contents << in.rdbuf();
	return contents.str();
}

bool Shader::CheckCompileErrors(GLuint object, bool program, const char* label)
{
	GLint success = GL_FALSE;

	if (program)
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
	}
	else
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
	}

	if (success == GL_TRUE)
		return true;

	GLint logLength = 0;
	if (program)
	{
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &logLength);
	}
	else
	{
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
	}

	std::string log(static_cast<size_t>(logLength), '\0');

	if (program)
	{
		glGetProgramInfoLog(object, logLength, nullptr, log.data());
	}
	else
	{
		glGetShaderInfoLog(object, logLength, nullptr, log.data());
	}

	std::cerr << "Shader " << label << " failed:\n" << log << '\n';

	return false;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	const std::string vertexCode = get_file_contents(vertexFile);
	const std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	CheckCompileErrors(vertexShader, false, "vertex compilation");

	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	CheckCompileErrors(fragmentShader, false, "fragment compilation");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	if (!CheckCompileErrors(ID, true, "program linking"))
	{
		Delete();
		throw std::runtime_error("Shader::Shader(): shader failed to create");
	}
}

Shader::~Shader()
{
	Delete();
}

void Shader::Bind() const
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	if (ID)
	{
		glDeleteProgram(ID);
		ID = 0;
	}
}

GLint Shader::GetUniformLocationChecked(const char* name) const
{
	const GLint location = glGetUniformLocation(ID, name);

	if (location == -1)
		throw std::runtime_error(std::string("Shader::GetUniformLocationChecked(): uniform '") + name + "' was not found in shader");

	return location;
}

void Shader::SetMat4(const char* name, const glm::mat4& value) const
{
	glUniformMatrix4fv(GetUniformLocationChecked(name), 1, GL_FALSE, glm::value_ptr(value));
}
