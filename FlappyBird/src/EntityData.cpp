#include "EntityData.h"

EntityData::EntityData(const std::string& texturePath)
{
	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	float texCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	int indices[] = {
		0, 1, 2, 2, 3, 0
	};

	m_shape = std::make_shared<Shape>(vertices, sizeof(vertices), indices, sizeof(indices), texCoords, sizeof(texCoords));
	if (texturePath.empty())
	{
		// texturePath is empty
		m_texture = nullptr;
	}
	else
	{
		m_texture = ResourceManager::GetTexture(texturePath);
	}
}
