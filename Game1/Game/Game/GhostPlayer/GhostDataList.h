#pragma once
#include "GhostCommon.h"

class GhostDataList : public GameObject
{
public:
	GhostDataList();

	~GhostDataList();

	void Start(D3DXVECTOR3* position, D3DXQUATERNION* rotation, Animation* animation);

	void Finish();

	void Update()override;

	std::list<GhostData>& GetGhostData()
	{
		return m_ghostData[m_stageNum];
	}
private:
	D3DXVECTOR3*	m_pPosition;
	D3DXQUATERNION* m_pRotation;
	Animation*		m_pAnimation;
	std::vector<std::list<GhostData>> m_ghostData;
	int				m_stageNum;
};

extern GhostDataList* g_ghostDataList;