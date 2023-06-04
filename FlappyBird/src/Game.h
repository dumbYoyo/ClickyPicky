#pragma once

#include "Window.h"
#include "Entity.h"
#include "MasterRenderer.h"
#include <stb/stb_image.h>

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

	Entity* m_player;
	Entity* entitiy;
	MasterRenderer* m_renderer;
};
