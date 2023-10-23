#include "Entity.h"

Entity::Entity(const std::string& texturePath, glm::vec3 position, float rotation, glm::vec2 scale) :
	Position(position), Rotation(rotation), Scale(scale)
{
	m_entityData = std::make_shared<EntityData>(texturePath);
	m_boundingBox = scale;
}

Entity::Entity() :
	Position(glm::vec3(0, 0, 0)), Rotation(0.0f), Scale(glm::vec2(100, 100))
{
	m_entityData = std::make_shared<EntityData>("");
	m_boundingBox = Scale;
}

/// <summary>
/// Setups up and sends all the stuff to the gpu
/// </summary>
void Entity::Render(Shader* shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(Rotation), glm::vec3(0, 0, 1));
	model = glm::translate(model, Position);
	model = glm::scale(model, glm::vec3(Scale, 1));

	shader->LoadMat4("model", model);
	shader->LoadInt("spriteSheetRows", 0);
	shader->LoadInt("spriteSheetColumns", 0);
	shader->LoadInt("time", 0);

	glDrawElements(GL_TRIANGLES, m_entityData->GetShape()->GetNumVertices(), GL_UNSIGNED_INT, 0);
}

void Entity::SetBoundingBox(float sizeX, float sizeY)
{
	m_boundingBox = glm::vec2(sizeX, sizeY);
}

bool Entity::CollidesWith(const Entity& other)
{
	if (std::fabs(Position.x - other.Position.x) < std::fabs(m_boundingBox.x / 2.f) + std::fabs(other.m_boundingBox.x / 2.f)) {
		if (std::fabs(Position.y - other.Position.y) < std::fabs(m_boundingBox.y / 2.f) + std::fabs(other.m_boundingBox.y / 2.f)) {
			return true;
		}
	}
	return false;
}
