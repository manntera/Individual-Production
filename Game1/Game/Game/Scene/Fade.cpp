#include "stdafx.h"
#include "Fade.h"

Fade* g_pFade = nullptr;

Fade::Fade() :
	m_fadeTime(0.5f),
	m_timer(m_fadeTime),
	m_sprite(),
	m_alpha(0.0f),
	m_isExcute(false),
	m_state(enFadeOut)

{
	Add(this, PRIORITY_MAX - 1);
}

Fade::~Fade()
{
	Delete(this);
}

void Fade::Init()
{
	Texture* texture = GetTextureResource().LoadTexture("Assets/sprite/Fade.png");
	m_sprite.Init(texture);
	m_sprite.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
}

void Fade::FadeIn()
{
	m_timer = 0.0f;
	m_state = enFadeIn;
	m_isExcute = true;
}
void Fade::FadeOut()
{
	m_timer = 0.0f;
	m_state = enFadeOut;
	m_isExcute = true;
}

void Fade::Update()
{
	//一定時間たつまでフェイド中
	if (m_timer < m_fadeTime)
	{
		m_timer += GetGameTime().GetDeltaFrameTime();
	}
	else
	{
		m_isExcute = false;
		m_timer = m_fadeTime;
	}
	//フェードしてる時間をアルファ値としてスプライトを半透明にする
	float alpha = m_timer / m_fadeTime;
	if (m_state == enFadeIn)
	{
		alpha = 1.0f - alpha;
	}
	m_sprite.SetAlpha(alpha);
}

void Fade::AfterDraw()
{
	m_sprite.Draw();
}