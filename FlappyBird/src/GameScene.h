#pragma once

#include <stb/stb_image.h>
#include "Scene.h"
#include "AnimatedEntity.h"
#include "MasterRenderer.h"
#include "MainMenuScene.h"
#include <vector>
#include <irrKlang/irrKlang.h>

class GameScene : public Scene
{
public:
	GameScene(const GameScene& obj) = delete;
	~GameScene();

	void Enter() override;
	static GameScene* Get();
	void Exit() override;
private:
	GameScene() {  }

	void Update(float dt) override;
	void Render() override;
	void CleanUp() override;

	void CheckCollisions();

	AnimatedEntity* m_player;
	glm::vec2 m_velocity, m_acceleration;

	Entity* m_background;
	std::vector<std::shared_ptr<Entity>> m_pipes;
	float m_spawnPipesElapsed;
	float m_spawnPipesTime;

	float m_worldMoveSpeed;
	bool m_flyingDisabled;

	MasterRenderer* m_renderer;
	irrklang::ISoundEngine* m_soundEngine;

	static GameScene* s_instance;

	float RandomFloat(float from, float to);
	float RandomFloatStep(float from, float to, float step);

	bool m_paused;
};
