#pragma once

#include "EntityRenderer.h"

class MasterRenderer
{
public:
	MasterRenderer();
	~MasterRenderer();

	void Render();
	void AddEntity(Entity* entity);
	void CreateProjectionMatrix();
private:
	EntityRenderer* m_entityRenderer;
	Shader* m_entityShader;
	std::unordered_map<EntityData, std::vector<Entity*>> m_entities;
};
