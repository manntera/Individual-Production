#pragma once

enum EnFadeState
{
	enFadeIn,
	enFadeOut,
};

class Fade : public GameObject
{
public:
	Fade();

	~Fade();

	void Init();

	void FadeIn();

	void FadeOut();

	void Update()override;

	void AfterDraw()override;

	EnFadeState GetCurrentState()
	{
		return m_state;
	}

	bool IsExcute()
	{
		return m_isExcute;
	}

private:
	float		m_fadeTime;
	float		m_timer;
	Sprite		m_sprite;
	float		m_alpha;
	bool		m_isExcute;
	EnFadeState	m_state;
};

extern Fade* g_pFade;