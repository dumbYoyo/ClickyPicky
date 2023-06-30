#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(Shader* shader)
{
	m_shader = shader;
}

void EntityRenderer::Render(std::unordered_map<EntityData, std::vector<Entity*>>& entities)
{
	for (auto& kv : entities)
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

		std::vector<Entity*>& batch = kv.second;
		for (Entity* entity : batch)
		{
			entity->Render(m_shader);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}
}
