#include "Sprite.h"
#include "../Engine.h"
#include "Texture.h"

Sprite::Sprite()
{
	m_pSprite = nullptr;
	m_pTexture = nullptr;
}

Sprite::~Sprite()
{
	if (m_pTexture != nullptr)
	{
		delete m_pTexture;
	}
	if (m_pSprite != nullptr)
	{
		m_pSprite->Release();
		delete m_pSprite;
	}
}

void Sprite::Init(char *filePath)
{
	
	D3DXCreateSprite(GetEngine().GetDevice(), &m_pSprite);
	m_pTexture = new Texture;
	m_pTexture->Load(filePath);
	float centerPosx = m_pTexture->GetWidth() / 2.0f;
	float centerPosy = m_pTexture->GetHeight() / 2.0f;
	float spritePosx = FRAME_BUFFER_WIDTH / 2.0f;
	float spritePosy = FRAME_BUFFER_HEIGHT / 2.0f;

	m_centerPosition = { centerPosx, centerPosy, 0.0f };
	m_position = { spritePosx, spritePosy, 0.0f };
}

void Sprite::Draw()
{

	m_pSprite->Begin(0);
	
	m_pSprite->Draw(m_pTexture->GetBody(),
		NULL,
		&m_centerPosition,
		&m_position,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	
	m_pSprite->End();
}

