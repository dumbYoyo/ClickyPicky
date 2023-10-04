#pragma once

#include "Scene.h"
#include "MasterRenderer.h"

class GameScene;

class MainMenuScene : public Scene
{
public:
	MainMenuScene(const MainMenuScene& obj) = delete;

	static MainMenuScene* Get();

	void Update(float dt) override;
	void Enter() override;
	void Exit() override;
private:
	MainMenuScene() { }

	static MainMenuScene* s_instance;

	MasterRenderer* m_renderer;

	void Render() override;
	void CleanUp() override;
};