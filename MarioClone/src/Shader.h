#pragma once

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include "glm/gtc/type_ptr.hpp"
#include <glad/glad.h>

class Shader {
private:
	unsigned int m_Id;
	std::unordered_map<std::string, unsigned int> uniformCache;

public:
	static std::unordered_map<std::string, Shader> Shaders;

public:
	static void LoadShader(const char* name, const char* vertFile, const char* fragFile);
	static Shader& GetShader(const char* name);
	void Bind() const;
	void UnBind() const;
	void Compile(const char* vertexCode, const char* fragmentCode);
	void SetInt(const char* name, int value);
	void SetInt(const char* name, int count, int* value);
	void SetFloat(const char* name, float value);
	void SetVector2(const char* name, glm::vec2 value);
	void SetVector3(const char* name, glm::vec3 value);
	void SetVector4(const char* name, glm::vec4 value);
	void SetMatrix4(const char* name, glm::mat4 value);

private:
	void CheckCompileError(unsigned int object, std::string type);
	unsigned int GetUniformCache(std::string name);
};