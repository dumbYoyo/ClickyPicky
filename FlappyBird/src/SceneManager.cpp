#include "SceneManager.h"

Game* Game::s_instance = NULL;

SceneManager::SceneManager()
{
	m_window = CreateWindow(1280, 720, "FlappyBird");

	m_nextScene = NULL;
	m_crntScene = Game::Get();
	m_crntScene->Enter();
}

SceneManager::~SceneManager()
{
	delete m_crntScene;
	delete m_nextScene;
}

void SceneManager::SetNextScene(Scene* newScene)
{
	m_nextScene = newScene;
}

void SceneManager::ChangeScene(double& steps)
{
	if (m_nextScene != NULL)
	{
		steps = 0;
		m_crntScene->Exit();
		m_nextScene->Enter();
		m_crntScene = m_nextScene;
		m_nextScene = NULL;
	}
}

void SceneManager::Run()
{
	double previous = glfwGetTime();
	double secsPerUpdate = 1.0 / 60.0;
	double steps = 0.0;
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(m_window))
	{
		glClearColor(50.f / 255.f, 45.f / 255.f, 50.f / 255.f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		double now = glfwGetTime();
		double delta = now - previous;
		previous = now;
		steps += delta;

		while (steps >= secsPerUpdate) {
			m_crntScene->Update((float)delta);
			steps -= secsPerUpdate;
		}

		m_crntScene->Render();

		if (KeyListener::GetKeyClicked(GLFW_KEY_TAB)) {
			SetNextScene(Game::Get());
		}

		KeyListener::EndFrame();
		MouseListener::EndFrame();

		glfwSwapBuffers(m_window);
		glfwPollEvents();

		ChangeScene(steps);
	}
}

GLFWwindow* SceneManager::GetGlfwWindow()
{
	return m_window;
}
