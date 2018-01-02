#pragma once
#include "GhostCommon.h"

class GhostPlayer : public GameObject
{
public:
	GhostPlayer();

	~GhostPlayer();

	void Init(SkinModelData& modelData, Light* light);

	bool Start()override;

	void Update()override;

	void Draw()override;

private:
	SkinModelData*	m_pPlayerModelData;
	Light*			m_pLight;
	SkinModelData m_modelData;
	SkinModel m_model;
	Animation m_animation;
	std::list<GhostData>::iterator m_ghostData;
	bool m_isActive;
	int m_currentAnimationNum;
};