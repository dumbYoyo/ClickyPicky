#pragma once

#include <stb/stb_image.h>
#include "Window.h"
#include "Entity.h"
#include "AnimatedEntity.h"
#include "MasterRenderer.h"

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

	AnimatedEntity* m_player;
	Entity* entitiy;
	MasterRenderer* m_renderer;
};
