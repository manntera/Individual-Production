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
#include "MapChip\StopTimeItem.h"
#include "MapChip\FallObject2.h"
#include "../Scene/GameScene.h"
#include "MapChip\GoalObject.h"

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
#include "Location1.h"
	},
	{
#include "Location2.h"
	},
	{
#include "Location4.h"
	},
	{
#include "Location5.h"
	}
};




Map::Map() :
	m_mapChip(),
	m_player(nullptr),
	m_stopTime(-1.0f),
	m_isLoad(false)
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
			m_player = New<Player>(PLAYER_PRIORITY);
			m_player->Init(mInfo.m_position, mInfo.m_rotation);
			break;
		case enMapTagGoal:
			mapChip = New<Goal>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagMoveFloor:
			mapChip = New<MoveFloor>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagSpring:
			mapChip = New<SpringObject>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagRotation:
			mapChip = New<RotationObject>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagHindrance:
			mapChip = New<HindranceObject>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagFall:
			mapChip = New<FallObject2>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagMapChip:
			mapChip = New<MapChip>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagScoreUp:
			mapChip = New<ScoreUpItem>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagStopTime:
			mapChip = New<StopTimeItem>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagGoalObject:
			mapChip = New<GoalObject>(STAGE_GIMMICK_PRIORITY);
			break;
		default:
			mapChip = New<StaticMapObject>(STAGE_GIMMICK_PRIORITY);
			break;
		}
		if (mapChip != nullptr)
		{
			//マップチップを生成
			mapChip->Init(mInfo.m_position, mInfo.m_rotation, mInfo.m_modelName);
			m_mapChip.push_back(mapChip);
			//マップチップに自身のイテレーターとマップのインスタンスを渡す(削除の時に使う)
			std::list<MapChip*>::iterator iterator = m_mapChip.end();
			iterator--;
			mapChip->SetIterator(this, iterator);
		}
	}
	for (MapChip* mapChip : m_mapChip)
	{
		mapChip->SetPlayer(m_player);
	}
}


void Map::Update()
{
	//マップの時間が止まっている時
	if (0.0f < m_stopTime)
	{
		m_stopTime -= GetGameTime().GetDeltaFrameTime();
		//時間がたったのでマップチップが動き出す
		if (m_stopTime < 0.0f)
		{
			for (MapChip* mapChip : m_mapChip)
			{
				mapChip->SetIsActive(true);
			}
		}
	}
	if (!m_isLoad)
	{
		GetGameScene().LoadComp();
		m_isLoad = true;
	}
}

void Map::StopTime()
{
	//マップチップの動きを一時停止
	m_stopTime = 10.0f;
	for (MapChip* mapChip : m_mapChip)
	{
		mapChip->SetIsActive(false);
	}
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