#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(Shader* shader)
{
	m_shader = shader;
}

EntityRenderer::~EntityRenderer()
{
	
}

void EntityRenderer::Render(std::unordered_map<EntityData, std::vector<Entity>>& entities)
{
	for (auto kv : entities)
	{
		EntityData entityData = kv.first;

		if (entityData.GetTexture() != nullptr)
		{
			m_shader->LoadInt("tex_sampler", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entityData.GetTexture()->GetTextureId());
		}

		glBindVertexArray(entityData.GetShape()->GetVao());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		std::vector<Entity>& batch = kv.second;
		for (Entity& entity : batch)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(entity.Rotation), glm::vec3(0, 0, 1));
			model = glm::translate(model, entity.Position);
			model = glm::scale(model, glm::vec3(entity.Scale, 1));
			m_shader->LoadMat4("model", model);

			glDrawElements(GL_TRIANGLES, entityData.GetShape()->GetNumVertices(), GL_UNSIGNED_INT, 0);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}
}
