#pragma once
#include "../common.h"
#include "Primitive.h"
class Texture;
class Sprite
{
public:

	Sprite();


	~Sprite();
	//������
	void Init(char *filePath);

	//�`��
	void Draw();

	//���W���Z�b�g
	void SetPosition(D3DXVECTOR2 position)
	{
		m_position = position;
	}

	D3DXVECTOR2 GetPosition()
	{
		return m_position;
	}

	void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}
	D3DXVECTOR2 GetSize()
	{
		return m_size;
	}

private:
	Texture*		m_pTexture;			//�e�N�X�`��
	D3DXVECTOR2		m_position;			//�X�v���C�g�̃E�B���h�E��ł̍��W
	D3DXVECTOR2		m_centerPosition;	//�X�v���C�g�̊�_��\�����W
	D3DXVECTOR2		m_size;
	LPD3DXEFFECT	m_pEffect;
	Primitive		m_primitive;
};