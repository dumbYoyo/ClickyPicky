#include "Game.h"

Game::Game()
{
	m_window = CreateWindow(1280, 720, "FlappyBird");

	m_player = new AnimatedEntity("res/Bird.png", glm::vec3(500, 500, 0), 0, glm::vec2(320, 110), AnimConfig("res/animConfig.cfg", 4, 1, 32, 11));

	m_renderer = new MasterRenderer();
}

Game::~Game()
{
	CleanUp();
}

void Game::Update(float dt)
{
	m_player->Update(dt);
}

void Game::Render()
{
	m_renderer->AddEntity(m_player);

	m_renderer->Render();
}

void Game::CleanUp()
{
	delete m_renderer;
	delete m_player;
}

void Game::Run()
{
	gladLoadGL();
	double previous = glfwGetTime();

	while (!glfwWindowShouldClose(m_window))
	{
		glClearColor(50.f/255.f, 45.f/255.f, 50.f/255.f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		double now = glfwGetTime();
		double elapsed = now - previous;
		previous = now;

		Update((float)elapsed);
		Render();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glfwTerminate();
}
