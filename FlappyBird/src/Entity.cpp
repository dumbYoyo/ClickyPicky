#include "Entity.h"

Entity::Entity(const std::string& texturePath, glm::vec3 position, float rotation, glm::vec2 scale) :
	Position(position), Rotation(rotation), Scale(scale)
{
	m_entityData = std::make_shared<EntityData>(texturePath);
}

Entity::Entity() :
	Position(glm::vec3(0, 0, 0)), Rotation(0.0f), Scale(glm::vec2(100, 100))
{
	m_entityData = std::make_shared<EntityData>("");
}

