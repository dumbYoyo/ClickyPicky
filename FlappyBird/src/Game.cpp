#include "Game.h"

Game::Game()
{
	m_window = CreateWindow(1280, 720, "FlappyBird");

	m_player = new AnimatedEntity("res/Frog.png", glm::vec3(500, 500, 0), 0, glm::vec2(200, 200), AnimConfig("res/config.cfg", 4, 3, 22, 20));
	entitiy = new Entity("res/pic.png", glm::vec3(900, 500, 0), 0, glm::vec2(300, 300));

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
	m_renderer->AddEntity(entitiy);

	m_renderer->Render();
}

void Game::CleanUp()
{
	delete m_renderer;
	delete m_player;
	delete entitiy;
}

void Game::Run()
{
	gladLoadGL();
	double previous = glfwGetTime();

	while (!glfwWindowShouldClose(m_window))
	{
		glClearColor(1, 0, 0, 1);
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
