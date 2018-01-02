#pragma once


class TitleScene : public GameObject
{
public:
	TitleScene();

	~TitleScene();

	bool Start()override;

	void Update()override;


	void AfterDraw()override;

private:
	Sprite	m_titleBack;
	Sprite	m_title;
	Sprite	m_start;
	Sprite	m_continue;
	Sprite	m_timeAttack;
	Sprite	m_arrow;
	int		m_choiceNum;
};