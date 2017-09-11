#pragma once
class Player;
class GameCamera;
class Test;

class GameScene : public GameObject
{
public:
	void Init();

	void Update()override;
	
	GameCamera* GetCamera()
	{
		return m_camera;
	}

	Player* GetPlayer()
	{
		return m_player;
	}

private:
	Player*			m_player;
	GameCamera*		m_camera;
	Test*			m_test;
};

extern GameScene *g_gameScene;