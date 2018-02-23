#pragma once
//�^�C���\���̂g�t�c

class TimeSprite : public GameObject
{
public:

	//�R���X�g���N�^
	TimeSprite();

	//�f�X�g���N�^
	~TimeSprite()override;

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void AfterDraw()override;

	//�^�C���擾
	float GetTime() const
	{
		return m_time;
	}

private:
	static const int	NUM_MAX = 10;						//�ꌅ�̐����̐�
	static const int	DIGIT_MAX = 2;						//���̐�
	static const int	TIME_MAX = 3;						//��؂�̐�
	Sprite				m_timeSprite;						//�^�C���X�v���C�g
	Sprite				m_colonSprite[TIME_MAX - 1];			//��؂�̃X�v���C�g
	Sprite				m_numSprite[TIME_MAX][DIGIT_MAX];	//�����̃X�v���C�g
	Texture*			m_numTexture[NUM_MAX];				//�����̃e�N�X�`��
	float				m_time;								//�^�C��
};