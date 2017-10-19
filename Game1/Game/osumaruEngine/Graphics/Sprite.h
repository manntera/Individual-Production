#pragma once
#include "Primitive.h"
#include "Texture.h"
class Texture;

//�X�v���C�g�N���X

class Sprite : Uncopyable
{
public:
	//�R���X�g���N�^
	Sprite();

	//�f�X�g���N�^
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

	//���W���擾
	D3DXVECTOR2 GetPosition()
	{
		return m_position;
	}

	//�T�C�Y��ݒ�
	void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	//�T�C�Y���擾
	D3DXVECTOR2 GetSize()
	{
		return m_size;
	}

	//�����������
	void Release();

private:
	float			m_alpha;
	Texture			m_texture;			//�e�N�X�`��
	D3DXVECTOR2		m_position;			//�X�v���C�g�̃E�B���h�E��ł̍��W
	D3DXVECTOR2		m_centerPosition;	//�X�v���C�g�̊�_��\�����W
	D3DXVECTOR2		m_size;				//�X�v���C�g�̃T�C�Y
	LPD3DXEFFECT	m_pEffect;			//�X�v���C�g�p�̃G�t�F�N�g
	Primitive		m_primitive;		//�v���~�e�B�u
};