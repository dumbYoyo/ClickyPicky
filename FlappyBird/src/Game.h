#pragma once

#include <stb/stb_image.h>
#include "Window.h"
#include "AnimatedEntity.h"
#include "MasterRenderer.h"
#include <vector>

class Game
{
public:
	Game();
	~Game();

	void Run();
private:
	GLFWwindow* m_window;

	void CleanUp();
	void Update(float dt);
	void Render();
	float RandomFloat(float from, float to);
	float RandomFloatStep(float from, float to, float step);

	AnimatedEntity* m_player;
	glm::vec2 m_velocity, m_acceleration;

	Entity* m_background;
	std::vector<std::shared_ptr<Entity>> m_pipes;
	float m_spawnPipesElapsed;
	float m_spawnPipesTime;

	MasterRenderer* m_renderer;
};
