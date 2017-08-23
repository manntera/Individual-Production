#pragma once
#include "../common.h"
class Texture;
class Sprite
{
public:

	Sprite();

	~Sprite();

	void Init(char *filePath);

	void Draw();
private:
	LPD3DXSPRITE m_pSprite;			//�X�v���C�g
	Texture* m_pTexture;			//�e�N�X�`��
	D3DXVECTOR3 m_position;			//�X�v���C�g�̃E�B���h�E��ł̍��W
	D3DXVECTOR3 m_centerPosition;	//�X�v���C�g�̊�_��\�����W

};