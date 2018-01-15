#include "stdafx.h"
#include "Map.h"
#include "MapChip/MapChip.h"
#include "MapChip\StaticMapObject.h"
#include "../Player/Player.h"
#include "MapChip\Goal.h"
#include "MapChip\MoveFloor.h"
#include "MapChip/SpringObject.h"
#include "MapChip\RotationObject.h"
#include "MapChip\HindranceObject.h"
#include "MapChip/FallObject.h"
#include "MapChip\ScoreUpItem.h"

struct MapChipInfo
{
	char*			m_modelName;
	D3DXVECTOR3		m_position;
	D3DXQUATERNION	m_rotation;
	EnMapChipTag	m_tag;
};

std::vector<std::vector<MapChipInfo>> mapChipInfo = 
{
	{
#include "Location4.h"
	},
	{
#include "Location2.h"
	},
	{
#include "Location1.h"
	}
};




Map::Map()
{

}

Map::~Map()
{
}

void Map::Init(int stageNum)
{
	for (MapChipInfo& mInfo : mapChipInfo[stageNum])
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
		case enMapTagFall:
			mapChip = New<FallObject>(stageGimmickPriority);
			break;
		case enMapTagMapChip:
			mapChip = New<MapChip>(stageGimmickPriority);
			break;
		case enMapTagScoreUp:
			mapChip = New<ScoreUpItem>(stageGimmickPriority);
			break;
		default:
			mapChip = New<StaticMapObject>(stageGimmickPriority);
			break;
		}

		if (mapChip != nullptr)
		{
			mapChip->Init(mInfo.m_position, mInfo.m_rotation, mInfo.m_modelName);
			m_mapChip.push_back(mapChip);
			std::list<MapChip*>::iterator iterator = m_mapChip.end();
			iterator--;
			mapChip->SetIterator(this, iterator);
		}
	}
}



void Map::Update()
{

}

void Map::MapChipErase(std::list<MapChip*>::iterator iterator)
{
	Delete(*iterator);
	iterator = m_mapChip.erase(iterator);
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
