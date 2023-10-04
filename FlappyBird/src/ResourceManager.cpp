#include "ResourceManager.h"

std::unordered_map<std::string, Shader*> ResourceManager::m_shaders;
std::unordered_map<std::string, std::shared_ptr<Texture>> ResourceManager::m_textures;

ResourceManager* ResourceManager::Get()
{
	if (s_instance != NULL)
	{
		return s_instance;
	}
	else
	{
		s_instance = new ResourceManager();
		return s_instance;
	}
}

void ResourceManager::LoadAll()
{
	LoadShaders("EntityShader", new Shader("res/vertex.glsl", "res/fragment.glsl"));
	LoadTextures("BirdTex", std::make_shared<Texture>("res/Bird.png"));
	LoadTextures("BackgroundTex", std::make_shared<Texture>("res/Background.png"));
	LoadTextures("PipeTex", std::make_shared<Texture>("res/Pipe.png"));
}

void ResourceManager::LoadShaders(std::string resourceName, Shader* shader)
{
	if (shader != nullptr)
		m_shaders.emplace(resourceName, shader);
}

void ResourceManager::LoadTextures(std::string resourceName, std::shared_ptr<Texture> texture)
{
	if (texture.get() != nullptr)
		m_textures.emplace(resourceName, texture);
}

Shader* ResourceManager::GetShader(std::string resourceName)
{
	if (m_shaders.count(resourceName))
		return m_shaders[resourceName];
	else
		std::cout << "Couldn't find the resource: " << resourceName;
	return nullptr;
}

std::shared_ptr<Texture> ResourceManager::GetTexture(std::string resourceName)
{
	if (m_textures.count(resourceName))
		return m_textures[resourceName];
	else
		std::cout << "Couldn't find the resource: " << resourceName;
	return nullptr;
}
