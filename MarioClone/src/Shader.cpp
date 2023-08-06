#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

std::unordered_map<std::string, Shader> Shader::Shaders;

void Shader::LoadShader(const char* name, const char* vertFile, const char* fragFile) {
	std::string vertCode, fragCode;

	try
	{
		std::ifstream vertexFile(vertFile);
		std::ifstream fragmentFile(fragFile);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vertexFile.rdbuf();
		fShaderStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertCode = vShaderStream.str();
		fragCode = fShaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "Load Shader Failed ! " << std::endl;
	}

	Shader shader;
	shader.Compile(vertCode.c_str(), fragCode.c_str());
	Shaders[name] = std::move(shader);
}


Shader& Shader::GetShader(const char* name)
{
	return Shader::Shaders[name];
}

void Shader::Bind() const {
	glUseProgram(m_Id);
}

void Shader::UnBind() const {
	glUseProgram(0);
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode) {
	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);
	CheckCompileError(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);
	CheckCompileError(fragment, "FRAGMENT");

	this->m_Id = glCreateProgram();
	glAttachShader(this->m_Id, vertex);
	glAttachShader(this->m_Id, fragment);
	glLinkProgram(this->m_Id);
	CheckCompileError(this->m_Id, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::CheckCompileError(unsigned int object, std::string type)  {
	int success;
	char infoLog[1024];

	if (type == "PROGRAM") {
		glGetProgramiv(object, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}

unsigned int Shader::GetUniformCache(std::string name) {
	if (uniformCache.find(name) == uniformCache.end())
		return uniformCache[name];
	unsigned int location = glGetUniformLocation(m_Id, name.c_str());
	uniformCache[name] = location;
	return location;
}

void Shader::SetInt(const char* name, int value)
{
	glUniform1i(GetUniformCache(name), value);
}

void Shader::SetInt(const char* name, int count, int* value)
{
	glUniform1iv(GetUniformCache(name), count, value);
}

void Shader::SetFloat(const char* name, float value)
{
	glUniform1f(GetUniformCache(name), value);
}

void Shader::SetVector2(const char* name, glm::vec2 value)
{
	glUniform2f(GetUniformCache(name), value.x, value.y);
}

void Shader::SetVector3(const char* name, glm::vec3 value)
{
	glUniform3f(GetUniformCache(name), value.x, value.y, value.z);
}

void Shader::SetVector4(const char* name, glm::vec4 value)
{
	glUniform4f(GetUniformCache(name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char* name, glm::mat4 value)
{
	glUniformMatrix4fv(GetUniformCache(name), 1, false, glm::value_ptr(value));
}