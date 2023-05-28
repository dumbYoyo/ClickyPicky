#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void LoadMat4(const char* uniformName, const glm::mat4& data);
	void LoadInt(const char* uniformName, const int& data);
	void LoadVec3(const char* uniformName, const glm::vec3& data);
	void Bind();
	void Unbind();

	unsigned int GetShaderProgram() { return m_shaderProgram; }

private:
	unsigned int m_shaderProgram;
	std::string loadShaderSource(const char* path);
};
