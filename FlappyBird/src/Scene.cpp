#include "Scene.h"

Scene::Scene() {  }

Scene::~Scene()
{
	glfwTerminate();
}

void Scene::SetManager(Manager* mgr)
{
	m_mgr = mgr;
}
