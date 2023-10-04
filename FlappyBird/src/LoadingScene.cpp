#include "LoadingScene.h"
#include "GameScene.h"

LoadingScene* LoadingScene::Get()
{
	if (s_instance != NULL)
	{
		return s_instance;
	}
	else
	{
		s_instance = new LoadingScene();
		return s_instance;
	}
}

void LoadingScene::Enter()
{
	m_timeLeft = 1.f;
	m_timeCount = 0.0f;
}

void LoadingScene::Exit() {  }

void LoadingScene::Update(float dt)
{
	m_timeCount += dt;
	if (m_timeCount >= m_timeLeft)
	{
		m_mgr->SetNextScene(m_mgr->GetPreviousScene());
		m_timeCount = 0.0f;
	}
}

void LoadingScene::Render() {  }

void LoadingScene::CleanUp() {  }
