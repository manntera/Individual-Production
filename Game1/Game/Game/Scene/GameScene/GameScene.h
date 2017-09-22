#pragma once
class Map;
class GameCamera;
class Test;
class Sky;
class Player;

class GameScene : public GameObject
{
public:
	void Init();

	void Update()override;
	
	Camera& GetCamera();

	Player* GetPlayer();

private:
	Map*			m_map;
	GameCamera*		m_camera;
	Test*			m_test;
	Sky*			m_sky;
};

extern GameScene *g_gameScene;