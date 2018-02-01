#pragma once
#include "GameScene.h"

class StageSelect : public GameObject
{
public:
	StageSelect();

	~StageSelect();

	bool Start()override;

	void Update()override;

	void Draw()override;
private:
	Sprite	m_stageNum[STAGE_NUM];
	Sprite	m_arrow;
	Sprite	m_back;
	int		m_choiceNum;
	bool	m_isBackScene;
};