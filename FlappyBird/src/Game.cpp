#include "Game.h"

Game::Game() :
	m_acceleration(0, 0), m_velocity(0, 0), m_spawnPipesTime(3.f), m_spawnPipesElapsed(0.f)
{
	m_window = CreateWindow(1280, 720, "FlappyBird");

	m_player = new AnimatedEntity("res/Bird.png", glm::vec3(500, 500, 0), 0, glm::vec2(320/1.5f, 110/1.5f), AnimConfig("res/animConfig.cfg", 4, 1, 32, 11, true));
	m_background = new Entity("res/Background.png", glm::vec3(640, 360, 0), 0, glm::vec2(1280, 720));

	m_renderer = new MasterRenderer();

	SetupWindowCallbacks(m_renderer, m_window);
}

Game::~Game()
{
	CleanUp();
}

// ladies and gentlemen, get ready to see some magic numbers down ahead
void Game::Update(float dt)
{
	m_player->Update(dt);

	m_acceleration.y = -10.8f;

	m_player->Position.y += m_velocity.y;

	if (KeyListener::GetKeyClicked(GLFW_KEY_SPACE))
		m_velocity.y = 300 * dt;
	else
		m_velocity += m_acceleration * dt;

	m_spawnPipesElapsed += dt;
	if (m_spawnPipesElapsed >= m_spawnPipesTime)
	{
		float x = RandomFloatStep(0, 1280, 100);
		float y = RandomFloat(700, 900);
		float y1 = RandomFloat(0, -170);
		std::shared_ptr<Entity> pipe = std::make_unique<Entity>("res/Pipe.png", glm::vec3(1400, y, 0), 0, glm::vec2(170, 560));
		std::shared_ptr<Entity> pipe2 = std::make_unique<Entity>("res/Pipe.png", glm::vec3(1400, y1, 0), 0, glm::vec2(170, -560));
		m_pipes.push_back(pipe);
		m_pipes.push_back(pipe2);

		m_spawnPipesElapsed = 0.f;
	}

	for (auto& pipe : m_pipes)
	{
		pipe->Position.x -= 100 * dt;
	}

	auto itr = m_pipes.begin();
	while (itr != m_pipes.end())
	{
		if (itr->get()->Position.x <= -100)
			itr = m_pipes.erase(itr);
		else
			++itr;
	}
}

void Game::Render()
{
	m_renderer->AddEntity(m_background);
	for (auto& pipe : m_pipes)
		m_renderer->AddEntity(pipe.get());
	m_renderer->AddEntity(m_player);

	m_renderer->Render();
}

float Game::RandomFloat(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float range = max - min;
	return min + (random * range);
}

float Game::RandomFloatStep(float from, float to, float step)
{
	return RandomFloat(from / step, to / step) * step;
}

void Game::CleanUp()
{
	delete m_renderer;
	delete m_player;
	delete m_background;
}

void Game::Run()
{
	double previous = glfwGetTime();
	double secsPerUpdate = 1.0 / 60.0;
	double steps = 0.0;
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(m_window))
	{
		glClearColor(50.f/255.f, 45.f/255.f, 50.f/255.f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		double now = glfwGetTime();
		double delta = now - previous;
		previous = now;
		steps += delta;

		while (steps >= secsPerUpdate) {
			Update((float)delta);
			steps -= secsPerUpdate;
		}

		Render();

		KeyListener::EndFrame();
		MouseListener::EndFrame();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glfwTerminate();
}
