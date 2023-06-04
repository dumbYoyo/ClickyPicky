#pragma once

#include "Shader.h"
#include "Entity.h"
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace std
{
	template<>
	struct hash<EntityData>
	{
		size_t operator()(const EntityData& key) const
		{
			return hash<std::string>()(key.m_texture->m_texturePath);
		}
	};

	template<>
	struct hash<EntityData*>
	{
		size_t operator()(const EntityData* key) const
		{
			return hash<EntityData>()(*key);
		}
	};
}

class EntityRenderer
{
public:
	EntityRenderer(Shader* shader);
	~EntityRenderer();
	void Render(std::unordered_map<EntityData, std::vector<Entity>>& entities);
private:
	Shader* m_shader;
};
