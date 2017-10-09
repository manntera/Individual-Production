#pragma once
class Player;

class PlayerGraspCliff
{
public:
	void Init(Player* position, float height);

	void Update();

	void Draw();

private:
	CollisionDetection	m_cliffRiseDetectionLow;
	CollisionDetection	m_cliffRiseDetectionUp;
	BoxCollider			m_boxColliderLow;
	BoxCollider			m_boxColliderUp;
	Player*		m_player;
	float		m_playerHeight;
};