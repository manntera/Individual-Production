#pragma once


class TimeAttackResult : public GameObject
{
public:
	TimeAttackResult();

	~TimeAttackResult();

	void Init(float time);

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;
private:
	int		m_choiceNum;
	Sprite m_arrow;
	Sprite m_finish;
	Sprite m_retry;
	float m_time;
	Sprite m_back;		//�Q�[���N���A�̃X�v���C�g
	static const int	NUM_MAX = 10;
	static const int	DIGIT_MAX = 2;
	static const int	TIME_MAX = 3;
	Sprite				m_timeSprite;
	Sprite				m_colonSprite[TIME_MAX];
	Sprite				m_numSprite[TIME_MAX][DIGIT_MAX];
	Texture*			m_numTexture[NUM_MAX];
};