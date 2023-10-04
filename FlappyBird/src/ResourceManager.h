#pragma once

#include <unordered_map>
#include "Shader.h"
#include "Texture.h"
#include <memory>

class ResourceManager
{
public:
	ResourceManager(const ResourceManager& obj) = delete;
	ResourceManager* Get();

	static void LoadShaders(std::string resourceName, Shader* shader);
	static void LoadTextures(std::string resourceName, std::shared_ptr<Texture>);
	
	static void LoadAll();

	static Shader* GetShader(std::string resourceName);
	static std::shared_ptr<Texture> GetTexture(std::string resourceName);
private:
	ResourceManager() {  }
	static ResourceManager* s_instance;

	static std::unordered_map<std::string, Shader*> m_shaders;
	static std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
};
