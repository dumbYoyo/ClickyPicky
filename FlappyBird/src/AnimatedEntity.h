#pragma once

#include "Entity.h"
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>

struct AnimConfig
{
	std::string m_animConfigFile;
	int m_numRows, m_numCols;
	float m_spriteWidth, m_spriteHeight;

	AnimConfig(const std::string& animConfigFile, int spriteSheetRows, int spriteSheetCols, float spriteWidth, float spriteHeight) :
		m_animConfigFile(animConfigFile), m_numRows(spriteSheetRows), m_numCols(spriteSheetCols), m_spriteWidth(spriteWidth), m_spriteHeight(spriteHeight)
	{
	}
};

class AnimatedEntity : public Entity
{
public:
	AnimatedEntity(const std::string& texturePath, glm::vec3 position, float rotation, glm::vec2 scale, const AnimConfig& animConfig);
	~AnimatedEntity();
	void Render(Shader* shader) override;
	void Update(float dt);
private:
	std::unordered_map<int, float> m_keyFrameDelaysMap;

	void LoadAnimConfigFile(const std::string& path);
	float m_currentFrameDelay;
	int m_currentFrameDelayIndex;
	float m_elapsedTimeDelay;

	float* m_texCoords;

	void PlayAnim();
};
