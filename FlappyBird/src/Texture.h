#pragma once

#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	unsigned int GetTextureId() { return m_textureId; }
	std::string& GetTexturePath() { return m_texturePath; }
	std::string m_texturePath;
private:
	unsigned int m_textureId;
	
};
