#pragma once
//�t�F�[�h������N���X

enum EnFadeState
{
	enFadeIn,
	enFadeOut,
};

class Fade : public GameObject
{
private:
	//�R���X�g���N�^
	Fade();

	//�f�X�g���N�^
	~Fade();

public:

	//�C���X�^���X���擾
	static Fade& GetInstance()
	{
		static Fade fade;
		return fade;
	}

	//������
	void Init();

	//�t�F�[�h�C�����鎞�ɊO������Ăяo���֐�
	void FadeIn();

	//�t�F�[�h�A�E�g���鎞�ɊO������Ăяo���֐�
	void FadeOut();

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void AfterDraw()override;

	//�t�F�[�h�̏�Ԃ��擾
	EnFadeState GetCurrentState() const
	{
		return m_state;
	}

	//�t�F�[�h�����H
	bool IsExcute() const
	{
		return m_isExcute;
	}

private:
	const float	m_fadeTime;		//�t�F�[�h���鎞��
	float		m_timer;		//�^�C�}�[
	Sprite		m_sprite;		//�X�v���C�g
	float		m_alpha;		//�s�����x
	bool		m_isExcute;		//�t�F�[�h�����H
	EnFadeState	m_state;		//�t�F�[�h�̏��
};

//�t�F�[�h���擾
static Fade& GetFade()
{
	return Fade::GetInstance();
}