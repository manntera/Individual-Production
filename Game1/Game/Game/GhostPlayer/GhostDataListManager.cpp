#include "stdafx.h"
#include "GhostDataListManager.h"
#include "../Scene/GameScene.h"
#include "../Scene/TimeAttackResult.h"

GhostDataListManager::GhostDataListManager() :
	m_pPosition(nullptr),
	m_pRotation(nullptr),
	m_pAnimation(nullptr),
	m_ghostData(),
	m_substitute(),
	m_stageNum(0),
	m_isActive(false)
{
	m_ghostData.resize(STAGE_NUM);
	for (int i = 0;i < STAGE_NUM;i++)
	{
		m_ghostData[i].time = 1000.0f;
	}
	Add(this, LAST_PRIORITY);
}

GhostDataListManager::~GhostDataListManager()
{

}

void GhostDataListManager::Start(const D3DXVECTOR3* position, const D3DXQUATERNION* rotation, const Animation* animation)
{
	m_stageNum = GetGameScene().GetStageNum();
	m_pPosition = position;
	m_pRotation = rotation;
	m_pAnimation = animation;
	m_isActive = true;
}

void GhostDataListManager::Finish(float time, bool isClear)
{
	//ゲームオーバーだった場合
	if (!isClear)
	{
		m_substitute.clear();
		m_pPosition = nullptr;
		m_pRotation = nullptr;
		m_pAnimation = nullptr;
		m_isActive = false;
		return;
	}
	//新しい記録が古い記録より早かった場合更新する
	if (time < m_ghostData[m_stageNum].time)
	{
		m_ghostData[m_stageNum].time = time;
		m_ghostData[m_stageNum].ghostData = m_substitute;
	}
	m_substitute.clear();
	m_pPosition = nullptr;
	m_pRotation = nullptr;
	m_pAnimation = nullptr;
	m_isActive = false;
}

void GhostDataListManager::Update()
{
	if (!m_isActive)
	{
		return;
	}
	m_substitute.push_back({ *m_pPosition, *m_pRotation, GetGameTime().GetDeltaFrameTime(), m_pAnimation->GetCurrentAnimationNum() });
}

void GhostDataListManager::GhostDataRead()
{
	FILE* file;
	for (int i = 0;i < STAGE_NUM;i++)
	{
		char filePath[64];
		sprintf(filePath, "Assets/SaveData/GhostData%d.txt", i);
		file = fopen(filePath, "r");
		if (file == NULL)
		{
			continue;
		}
		const int rate = 1000000;
		const int rateNum = 11;
		char data[rateNum + 2] = { 0 };
		D3DXVECTOR3 position;
		D3DXQUATERNION rotation;
		float animationTime;
		int animationNum;
		const int dataNum = 8;
		const int animationEnumDigit = 2;
		float* pData[dataNum] = { &position.x, &position.y, &position.z,
			&rotation.x, &rotation.y, &rotation.z, &rotation.w, &animationTime };
		while (true)
		{
			bool flg = false;
			int inNum;
			for (int j = 0;j < dataNum;j++)
			{
				inNum = 0;
				fgets(data, rateNum + 2, file);
				if (j == 0)
				{
					if (feof(file))
					{
						flg = true;
						break;
					}
				}
				int sign = 1;
				if (data[0] == '-')
				{
					sign *= -1;
				}
				for (int k = 1;k < rateNum;k++)
				{
					inNum *= 10;
					inNum += data[k] - '0';
				}
				*pData[j] = (float)(inNum * sign) / (float)rate;
			}
			if (flg)
			{
				break;
			}
			inNum = 0;
			fgets(data, animationEnumDigit + 2, file);
			for (int k = 0;k < animationEnumDigit;k++)
			{
				inNum *= 10;
				inNum += data[k] - '0';
			}
			animationNum = inNum;
			m_ghostData[i].ghostData.push_back({position, rotation, animationTime, animationNum});			
		}
		m_ghostData[i].time = TimeAttackResult::GetTime(i, 0);
		fclose(file);
	}
}

void GhostDataListManager::GhostDataSave()
{
	FILE* file;
	for (int i = 0;i < STAGE_NUM;i++)
	{
		char filePath[64];
		sprintf(filePath, "Assets/SaveData/GhostData%d.txt", i);
		file = fopen(filePath, "w");
		std::list<GhostData>::iterator it = m_ghostData[i].ghostData.begin();
		while (it != m_ghostData[i].ghostData.end())
		{
			const int rate = 1000000;
			const int dataNum = 8;
			float* data[dataNum] = { &it->position.x, &it->position.y, &it->position.z,
				&it->rotation.x, &it->rotation.y, &it->rotation.z, &it->rotation.w, &it->animationUpdateTime };
			for (int j = 0;j < dataNum;j++)
			{
				if (*data[j] < 0.0f)
				{
					fprintf(file, "%011d\n", (int)(*data[j] * rate));
				}
				else
				{
					fprintf(file, "+%010d\n", (int)(*data[j] * rate));
				}
			}
			fprintf(file, "%02d\n", it->currentAnimationNum);
			it++;
		}
		fclose(file);
	}
}