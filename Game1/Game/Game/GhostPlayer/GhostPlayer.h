#pragma once
#include "GhostCommon.h"

class GhostPlayer : public GameObject
{
public:
	GhostPlayer();

	~GhostPlayer();

	void Init(SkinModelData& modelData, Light* light);

	void Start()override;

	void Update()override;

	void Draw()override;

private:
	SkinModelData m_modelData;
	SkinModel m_model;
	Animation m_animation;
	std::list<GhostData>::iterator m_ghostData;
	bool m_isActive;
	int m_currentAnimationNum;
};