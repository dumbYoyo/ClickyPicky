#pragma once

#include "Scene.h"

class GameScene;

class LoadingScene : public Scene
{
public:
	LoadingScene(const LoadingScene& obj) = delete;

	static LoadingScene* Get();

	void Update(float dt) override;
	void Enter() override;
	void Exit() override;
private:
	LoadingScene() { }

	static LoadingScene* s_instance;

	void Render() override;
	void CleanUp() override;

	float m_timeLeft;
	float m_timeCount;
};