#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
{
	m_entityShader = new Shader("res/vertex.glsl", "res/fragment.glsl");
	m_entityRenderer = new EntityRenderer(m_entityShader);

	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.1f, 100.0f);
	m_entityShader->LoadMat4("proj", proj);
}

MasterRenderer::~MasterRenderer()
{
	delete m_entityRenderer;
	delete m_entityShader;
	m_entities.clear();
}

void MasterRenderer::Render()
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));

	m_entityShader->Bind();
	m_entityShader->LoadMat4("view", view);
	m_entityRenderer->Render(m_entities);
	m_entityShader->Unbind();

	m_entities.clear();
}

void MasterRenderer::AddEntity(Entity* entity)
{
	std::shared_ptr<EntityData> entityData = entity->GetEntityData();
	std::vector<Entity>* batch = nullptr;

	auto itr = m_entities.find(*entityData);
	if (itr != m_entities.end())
	{
		batch = &itr->second;
	}
	else
	{
		std::vector<Entity> newBatch;
		m_entities.emplace(*entityData, newBatch);
		batch = &m_entities[*entityData];
	}

	if (batch == nullptr)
	{
		std::cout << "Batch couldnt be created\n";
		return;
	}

	batch->push_back(*entity);
}
