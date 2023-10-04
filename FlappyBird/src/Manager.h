#pragma once

#include <iostream>
#include "ResourceManager.h"

class Scene;
class GameScene;
class LoadingScene;
class MainMenuScene;

class Manager
{
public:
	Manager();
	~Manager();

	void SetNextScene(Scene* newScene);
	void Run();
	void TriggerUpdatePaused();

	Scene* GetPreviousScene();

	GLFWwindow* GetGlfwWindow();
private:
	Scene* m_crntScene;
	Scene* m_prevScene;
	Scene* m_nextScene;
	GLFWwindow* m_window;

	float m_delta;
	float m_steps;

	float m_waitTime;
	float m_waitTimeElapsed;
	bool m_wait;

	bool m_updatePaused;
	bool m_gamePaused;

	void ChangeScene();
};
