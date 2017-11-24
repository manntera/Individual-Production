#include "stdafx.h"
#include "Map.h"
#include "MapChip/MapChip.h"
#include "MapChip\StaticMapObject.h"
#include "../Player/Player.h"
#include "MapChip\Goal.h"
#include "MapChip\MoveFloor.h"
#include "MapChip/SpringObject.h"
#include "MapTagEnum.h"
#include "MapChip\RotationObject.h"
#include "MapChip\HindranceObject.h"

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
			m_player = New<Player>(playerPriority);
			m_player->Init(mInfo.m_position, mInfo.m_rotation);
			break;

		case enMapTagGoal:
			mapChip = New<Goal>(stageGimmickPriority);
			break;

		case enMapTagMoveFloor:
			mapChip = New<MoveFloor>(stageGimmickPriority);
			break;

		case enMapTagSpring:
			mapChip = New<SpringObject>(stageGimmickPriority);
			break;

		case enMapTagRotation:
			mapChip = New<RotationObject>(stageGimmickPriority);
			break;

		case enMapTagHindrance:
			mapChip = New<HindranceObject>(stageGimmickPriority);
			break;

		default:
			mapChip = New<StaticMapObject>(stageGimmickPriority);
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

void Map::BeforeDead()
{
	Delete(m_player);
	for (MapChip* mapchip : m_mapChip)
	{
		Delete(mapchip);
	}
	m_mapChip.clear();
}