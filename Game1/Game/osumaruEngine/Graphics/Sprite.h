#pragma once

//�X�v���C�g�N���X

class Sprite : Uncopyable
{
public:
	//�R���X�g���N�^
	Sprite();

	//�f�X�g���N�^
	~Sprite();

	//������
	void Init(Texture* texture);

	//�`��
	void Draw();

	//���W���Z�b�g
	void SetPosition(D3DXVECTOR2 position)
	{
		m_position = position;
	}

	//���W���擾
	const D3DXVECTOR2& GetPosition() const
	{
		return m_position;
	}

	//�T�C�Y��ݒ�
	void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	//�s�����x��ݒ�
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	//�T�C�Y���擾
	const D3DXVECTOR2& GetSize() const
	{
		return m_size;
	}

	//�����������
	void Release();

	void SetTexture(Texture* pTexture)
	{
		m_pTexture = pTexture;
	}

private:
	float			m_alpha;
	Texture*		m_pTexture;			//�e�N�X�`��
	D3DXVECTOR2		m_position;			//�X�v���C�g�̃E�B���h�E��ł̍��W
	D3DXVECTOR2		m_centerPosition;	//�X�v���C�g�̊�_��\�����W
	D3DXVECTOR2		m_size;				//�X�v���C�g�̃T�C�Y
	LPD3DXEFFECT	m_pEffect;			//�X�v���C�g�p�̃G�t�F�N�g
	Primitive		m_primitive;		//�v���~�e�B�u
};