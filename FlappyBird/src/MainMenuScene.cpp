#include "MainMenuScene.h"
#include "GameScene.h"

void MainMenuScene::Enter()
{
	m_renderer = new MasterRenderer();

	SetupWindowCallbacks(m_renderer, m_mgr);
}

MainMenuScene* MainMenuScene::Get()
{
	if (s_instance != NULL)
	{
		return s_instance;
	}
	else
	{
		s_instance = new MainMenuScene();
		return s_instance;
	}
}

void MainMenuScene::Update(float dt)
{
	if (KeyListener::GetKeyClicked(GLFW_KEY_SPACE))
		m_mgr->SetNextScene(GameScene::Get());
}


void MainMenuScene::Exit() {  }

void MainMenuScene::Render() {  }

void MainMenuScene::CleanUp() {  }

