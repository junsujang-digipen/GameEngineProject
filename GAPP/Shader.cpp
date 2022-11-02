/* Start Header -------------------------------------------------------
Copyright (C) <current year in format 2022> DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Shader.cpp
Purpose: For compile and linking shaders
Language: c++
Platform: x64
Project: junsu.jang, CS300, Assignment 1 - Render an OBJ file
Author: Junsu Jang, junsu.jang, 0055891
Creation date: 09/29/2022
End Header --------------------------------------------------------*/
#include "pch.h"
#include "Shader.h"

Shader::Shader()
{
	shdrProgram = glCreateProgram();
}

Shader::~Shader()
{
	unuseProgram();
	glDeleteProgram(shdrProgram);
}

GLuint Shader::compileShader(GLuint ShaderType, const char* source)
{
	GLuint shdr{ glCreateShader(ShaderType) };
	const char* sptr = source;
	glShaderSource(shdr, 1, &sptr, nullptr);
	glCompileShader(shdr);
	GLint shader_compiled;
	glGetShaderiv(shdr, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(shdr, 1024, &log_length, message);
		std::cout << message << std::endl;
		// Write the error to a log
	}
	return shdr;
}

void Shader::attachShader(GLuint shdr)
{
	glAttachShader(shdrProgram, shdr);
	shdrs.push_back(shdr);
}

void Shader::linkProgram()
{
	glLinkProgram(shdrProgram);

	// Check the program
	GLint Result{};
	glGetProgramiv(shdrProgram, GL_LINK_STATUS, &Result);
	if (Result != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(shdrProgram, 1024, &log_length, message);
		std::cout << message << std::endl;
		// Write the error to a log
	}

	for (auto& shdr:shdrs) {
		glDeleteShader(shdr);
	}
	shdrs.clear();
}

GLuint Shader::getHandle()
{
	return shdrProgram;
}

void Shader::useProgram()
{
	glUseProgram(shdrProgram);
}

void Shader::unuseProgram()
{
	glUseProgram(0);
}

void Shader::sendUniformMatrix4fv(const GLchar* name, const glm::mat4& data)
{
	useProgram();
	GLint loc = glGetUniformLocation(shdrProgram, name);
	if (loc >= 0) {
		glUniformMatrix4fv(loc, 1, GL_FALSE, &data[0][0]);
	}
	else {
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
	}
	unuseProgram();
}

void Shader::sendUniformMatrix3fv(const GLchar* name, const glm::mat3& data)
{
	useProgram();
	GLint loc = glGetUniformLocation(shdrProgram, name);
	if (loc >= 0) {
		glUniformMatrix3fv(loc, 1, GL_FALSE, &data[0][0]);
	}
	else {
		std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
	}
	unuseProgram();
}
