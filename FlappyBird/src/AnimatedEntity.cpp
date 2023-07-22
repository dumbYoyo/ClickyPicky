#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(const std::string& texturePath, glm::vec3 position, float rotation, glm::vec2 scale, const AnimConfig& animConfig) :
	Entity(texturePath, position, rotation, scale), m_currentFrameDelayIndex(1), m_elapsedTimeDelay(0), m_animConfig(animConfig), m_shouldLoop(true)
{
	LoadAnimConfigFile(animConfig.m_animConfigFile);
	m_currentFrameDelay = m_keyFrameDelaysMap.at(0);

	// default tex coords
	m_texCoords = new float[8] {
		0, 0, // top left
		0, animConfig.m_spriteHeight / animConfig.m_spriteSheetHeight, // bottom left
		animConfig.m_spriteWidth / animConfig.m_spriteSheetWidth, animConfig.m_spriteHeight / animConfig.m_spriteSheetHeight, // bottom right
		animConfig.m_spriteWidth / animConfig.m_spriteSheetWidth, 0 // top right
	};
	glBindBuffer(GL_ARRAY_BUFFER, GetEntityData()->GetShape()->GetTbo());
	glBufferSubData(GL_ARRAY_BUFFER, 0, GetEntityData()->GetShape()->m_texCoordsSize, m_texCoords);
}

void AnimatedEntity::Render(Shader* shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(Rotation), glm::vec3(0, 0, 1));
	model = glm::translate(model, Position);
	model = glm::scale(model, glm::vec3(Scale, 1));

	shader->LoadMat4("model", model);

	glDrawElements(GL_TRIANGLES, GetEntityData()->GetShape()->GetNumVertices(), GL_UNSIGNED_INT, 0);
}

AnimatedEntity::~AnimatedEntity()
{
	delete[] m_texCoords;
}

void AnimatedEntity::LoadAnimConfigFile(const std::string& path)
{
	std::ifstream fin;
	fin.open(path);
	std::vector<float> delaysVector;

	std::string line;
	while (getline(fin, line))
	{
		size_t prev = 0, pos;
		while ((pos = line.find_first_of(" ,", prev)) != std::string::npos) // npos - until the end of the string
		{
			if (pos > prev)
				delaysVector.push_back(std::stof(line.substr(prev, pos - prev)));

			prev = pos + 1;
		}
		if (prev < line.length())
			delaysVector.push_back(std::stof(line.substr(prev, std::string::npos)));
	}

	fin.close();

	for (int i = 0; i < delaysVector.size() - 1; ++i)
	{
		if (i % 2 == 0)
			m_keyFrameDelaysMap.emplace((int)delaysVector[i], delaysVector[i + 1]);
	}
}

void AnimatedEntity::PlayAnim()
{
	glBindBuffer(GL_ARRAY_BUFFER, GetEntityData()->GetShape()->GetTbo());
	glBufferSubData(GL_ARRAY_BUFFER, 0, GetEntityData()->GetShape()->m_texCoordsSize, m_texCoords);

	for (int i = 0; i < 8; i++)
	{
		if (i % 2 == 0)
			m_texCoords[i] += m_animConfig.m_spriteWidth / m_animConfig.m_spriteSheetWidth;
	}

	if (m_texCoords[6] >= 1)
	{
		for (int i = 0; i < 8; i++)
		{
			if (i % 2 != 0) {
				m_texCoords[i] += m_animConfig.m_spriteHeight / m_animConfig.m_spriteSheetHeight;
			}
		}
		m_texCoords[0] = 0;
		m_texCoords[2] = 0;
		m_texCoords[4] = m_animConfig.m_spriteWidth / m_animConfig.m_spriteSheetWidth;
		m_texCoords[6] = m_animConfig.m_spriteWidth / m_animConfig.m_spriteSheetWidth;
	}
}

void AnimatedEntity::Update(float dt)
{
	m_elapsedTimeDelay += dt;
	if (m_elapsedTimeDelay >= m_currentFrameDelay && m_currentFrameDelayIndex <= m_keyFrameDelaysMap.size())
	{
		PlayAnim();
		if (m_currentFrameDelayIndex <= m_keyFrameDelaysMap.size() - 1)
			m_currentFrameDelay = m_keyFrameDelaysMap.at(m_currentFrameDelayIndex);
		if (!m_shouldLoop)
			++m_currentFrameDelayIndex;
		m_elapsedTimeDelay = 0;
	}
}
