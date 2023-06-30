#pragma once

#include <glm/glm.hpp>
#include "EntityData.h"
#include "Shader.h"

class Entity
{
public:
	Entity(const std::string& texturePath, glm::vec3 position, float rotation, glm::vec2 scale);
	Entity();

	float Rotation;
	glm::vec3 Position;
	glm::vec2 Scale;

	std::shared_ptr<EntityData> GetEntityData() { return m_entityData; }
	virtual void Render(Shader* shader);
private:
	std::shared_ptr<EntityData> m_entityData;
};
