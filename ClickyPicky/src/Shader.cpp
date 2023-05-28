#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexShaderSource = loadShaderSource(vertexPath);
	std::string fragmentShaderSource = loadShaderSource(fragmentPath);

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	int success;
	char infoLog[512];

	const char* v = vertexShaderSource.c_str();
	const char* f = fragmentShaderSource.c_str();

	glShaderSource(vertexShader, 1, &v, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << vertexPath << ": " << infoLog << "\n";
	}

	glShaderSource(fragmentShader, 1, &f, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << fragmentPath << ": " << infoLog << "\n";
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
		std::cout << "Shader program: " << infoLog << "\n";
	}
	glValidateProgram(m_shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	Unbind();
	glDeleteProgram(m_shaderProgram);
}

void Shader::LoadMat4(const char* uniformName,  const glm::mat4& data)
{
	this->Bind();
	unsigned int location = glGetUniformLocation(m_shaderProgram, uniformName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
}

void Shader::LoadInt(const char* uniformName, const int& data)
{
	this->Bind();
	unsigned int location = glGetUniformLocation(m_shaderProgram, uniformName);
	glUniform1i(location, data);
}

void Shader::LoadVec3(const char* uniformName, const glm::vec3& data)
{
	this->Bind();
	unsigned int location = glGetUniformLocation(m_shaderProgram, uniformName);
	glUniform3f(location, data.x, data.y, data.z);
}

void Shader::Bind()
{
	glUseProgram(m_shaderProgram);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

std::string Shader::loadShaderSource(const char* path)
{
	std::ifstream in(path, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}