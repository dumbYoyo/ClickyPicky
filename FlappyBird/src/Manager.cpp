#include "Manager.h"
#include "Scene.h"
#include "GameScene.h"
#include "LoadingScene.h"
#include "MainMenuScene.h"

GameScene* GameScene::s_instance = NULL;
LoadingScene* LoadingScene::s_instance = NULL;
MainMenuScene* MainMenuScene::s_instance = NULL;

ResourceManager* ResourceManager::s_instance = NULL;

Manager::Manager()
{
	m_window = CreateWindow(1280, 720, "FlappyBird");
	m_delta = 0.f;
	m_steps = 0.f;
	m_wait = false;
	m_waitTime = 0.21f;
	m_waitTimeElapsed = 0.f;
	m_updatePaused = false;
	m_gamePaused = false;

	ResourceManager::LoadAll();

	m_nextScene = NULL;
	m_prevScene = NULL;
	m_crntScene = MainMenuScene::Get();
	m_crntScene->SetManager(this);
	m_crntScene->Enter();
}

Manager::~Manager()
{
	delete m_crntScene;
	delete m_nextScene;
}

void Manager::SetNextScene(Scene* newScene)
{
	if (newScene == nullptr)
		printf("the scene given in SetNextScene(Scene* newScene) is nullptr!\n");
	m_nextScene = newScene;
}

void Manager::ChangeScene()
{
	if (m_nextScene != NULL)
	{
		m_wait = true;
		m_delta = 0.016f;
		m_prevScene = m_crntScene;
		m_crntScene->Exit();
		m_nextScene->Enter();
		m_crntScene = m_nextScene;
		m_crntScene->SetManager(this);
		m_nextScene = NULL;
	}
}

void Manager::Run()
{
	float previous = (float)glfwGetTime();
	float secsPerUpdate = 1.0f / 60.0f;
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(m_window))
	{
		glClearColor(50.f / 255.f, 45.f / 255.f, 50.f / 255.f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		float now = (float)glfwGetTime();
		if (!m_wait)
			m_delta = now - previous;
		previous = now;
		m_steps += m_delta;

		ChangeScene();

		while (m_steps >= secsPerUpdate)
		{
			if (m_updatePaused)
				continue;

			m_crntScene->Update(m_delta);
			m_steps -= secsPerUpdate;

			if (m_wait)
			{
				m_waitTimeElapsed += m_delta;
				if (m_waitTimeElapsed > m_waitTime)
				{
					m_wait = false;
					m_waitTimeElapsed = 0.f;
				}
			}
		}

		m_crntScene->Render();

		KeyListener::EndFrame();
		MouseListener::EndFrame();
		
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void Manager::TriggerUpdatePaused()
{
	m_updatePaused = !m_updatePaused;
}

Scene* Manager::GetPreviousScene()
{
	return m_prevScene;
}

GLFWwindow* Manager::GetGlfwWindow()
{
	return m_window;
}
