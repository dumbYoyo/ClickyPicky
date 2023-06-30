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

/// <summary>
/// Only to be called by the entityRenderer, not by the user, usually.
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
