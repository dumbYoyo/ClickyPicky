#include "GameScene.h"

void GameScene::Enter()
{
	m_acceleration = glm::vec2(0, -1000.8f);
	m_velocity = glm::vec2(0, 0);
	m_spawnPipesTime = 3.f;
	m_spawnPipesElapsed = 0.f;
	m_worldMoveSpeed = 100.f;
	m_flyingDisabled = false;

	m_player = new AnimatedEntity("BirdTex", glm::vec3(500, 500, 0), 0, glm::vec2(320 / 1.5f, 110 / 1.5f), AnimConfig("res/animConfig.cfg", 4, 1, 32, 11, true));
	m_background = new Entity("BackgroundTex", glm::vec3(640, 360, 0), 0, glm::vec2(1280, 720));

	m_renderer = new MasterRenderer();
	m_soundEngine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT,
		irrklang::ESEO_MULTI_THREADED | irrklang::ESEO_LOAD_PLUGINS | irrklang::ESEO_USE_3D_BUFFERS);

	m_soundEngine->play2D("res/heroes.mp3", true);
}

GameScene::~GameScene()
{
	CleanUp();
}

// at this point i dont even care about the quality of the code, i just want to finish this thing
GameScene* GameScene::Get()
{
	if (s_instance != NULL)
	{
		return s_instance;
	}
	else
	{
		s_instance = new GameScene();
		return s_instance;
	}
}

// ladies and gentlemen, get ready to see some magic numbers down ahead
void GameScene::Update(float dt)
{
	m_player->Update(dt);
	m_worldMoveSpeed += dt;

	m_player->Position.y += m_velocity.y * dt;

	if (KeyListener::GetKeyClicked(GLFW_KEY_SPACE) && !m_flyingDisabled)
		m_velocity.y = 20000 * dt;
	else
		m_velocity += m_acceleration * dt;

	m_spawnPipesElapsed += dt;
	if (m_spawnPipesElapsed >= m_spawnPipesTime && !m_flyingDisabled)
	{
		float x = RandomFloatStep(0, 1280, 100);
		float y = RandomFloat(700, 900);
		float y1 = RandomFloat(0, -170);
		std::shared_ptr<Entity> pipe = std::make_unique<Entity>("PipeTex", glm::vec3(1400, y, 0), 0.f, glm::vec2(170, 560));
		std::shared_ptr<Entity> pipe2 = std::make_unique<Entity>("PipeTex", glm::vec3(1400, y1, 0), 0.f, glm::vec2(170, -560));
		m_pipes.push_back(pipe);
		m_pipes.push_back(pipe2);

		m_spawnPipesElapsed = 0.f;
	}

	for (auto& pipe : m_pipes)
	{
		pipe->Position.x -= m_worldMoveSpeed * dt;
	}

	auto itr = m_pipes.begin();
	while (itr != m_pipes.end())
	{
		if (itr->get()->Position.x <= -100)
			itr = m_pipes.erase(itr);
		else
			++itr;
	}

	CheckCollisions();

	if (KeyListener::GetKeyClicked(GLFW_KEY_TAB))
		m_mgr->SetNextScene(GameScene::Get());
	if (KeyListener::GetKeyClicked(GLFW_KEY_Q))
		m_mgr->SetNextScene(MainMenuScene::Get());
}

void GameScene::Render()
{
	m_renderer->AddEntity(m_background);
	for (auto& pipe : m_pipes)
		m_renderer->AddEntity(pipe.get());
	m_renderer->AddEntity(m_player);

	m_renderer->Render();
}

void GameScene::Exit()
{
	CleanUp();
}

void GameScene::CheckCollisions()
{
	for (auto& pipe : m_pipes)
	{
		if (m_player->CollidesWith(*pipe))
		{
			m_worldMoveSpeed = 0;
			m_flyingDisabled = true;
			m_player->ResetAnim();
		}
	}
}

float GameScene::RandomFloat(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float range = max - min;
	return min + (random * range);
}

float GameScene::RandomFloatStep(float from, float to, float step)
{
	return RandomFloat(from / step, to / step) * step;
}

void GameScene::CleanUp()
{
	delete m_renderer;
	delete m_player;
	delete m_background;
	m_soundEngine->drop(); // drop() closes/deletes it
	m_pipes.clear();
}
