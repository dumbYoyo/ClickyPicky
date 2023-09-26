#pragma once

#include <iostream>
#include "Scene.h"
#include "Game.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void SetNextScene(Scene* newScene);
	void Run();

	GLFWwindow* GetGlfwWindow();
private:
	Scene* m_crntScene;
	Scene* m_nextScene;
	GLFWwindow* m_window;

	void ChangeScene(double& steps);
};
