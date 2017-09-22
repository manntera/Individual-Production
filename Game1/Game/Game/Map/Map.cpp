#include "stdafx.h"
#include "Map.h"
#include "MapChip/MapChip.h"
#include "MapChip\StaticMapObject.h"
#include "../Player/Player.h"
#include "MapTagEnum.h"

struct MapChipInfo
{
	char*			m_modelName;
	D3DXVECTOR3		m_position;
	D3DXQUATERNION	m_rotation;
	EnMapChipTag	m_tag;
};
MapChipInfo mapChipInfo[] = 
{
#include "Location.h"
};


Map::Map()
{

}

Map::~Map()
{

}

void Map::Init()
{
	for (MapChipInfo& mInfo : mapChipInfo)
	{
		MapChip* mapChip = nullptr;

		switch (mInfo.m_tag)
		{
		case enMapTagPlayer:
			m_player = New<Player>();
			m_player->Init(mInfo.m_position, mInfo.m_rotation);
			break;
		default:
			mapChip = New<StaticMapObject>();
			break;

		}

		if (mapChip != nullptr)
		{
			mapChip->Init(mInfo.m_position, mInfo.m_rotation, mInfo.m_modelName);
			m_mapChip.push_back(mapChip);
		}
	}
}

void Map::Start()
{

}

void Map::Update()
{

}

