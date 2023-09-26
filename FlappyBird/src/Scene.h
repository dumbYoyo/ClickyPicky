#pragma once

#include "Window.h"

class SceneManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Render() = 0;
	virtual void Update(float dt) = 0;
	virtual void CleanUp() = 0;
};
