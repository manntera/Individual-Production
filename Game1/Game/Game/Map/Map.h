#pragma once
class MapChip;
class Player;


class Map : public GameObject
{
public:
	Map();

	~Map();

	void Init();

	void Start()override;

	void Update()override;

	Player* GetPlayer()
	{
		return m_player;
	}

private:
	std::vector<MapChip*> m_mapChip;
	Player*	m_player;
	
};
