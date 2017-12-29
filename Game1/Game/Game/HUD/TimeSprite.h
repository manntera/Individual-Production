#pragma once

class TimeSprite : public GameObject
{
public:

	//�R���X�g���N�^
	TimeSprite();

	//�f�X�g���N�^
	~TimeSprite()override;

	void Start()override;

	void Update()override;

	void Draw()override;

private:
	static const int	NUM_MAX = 10;
	static const int	DIGIT_MAX = 2;
	static const int	TIME_MAX = 3;
	Sprite				m_timeSprite;
	Sprite				m_colonSprite[TIME_MAX];
	Sprite				m_numSprite[TIME_MAX][DIGIT_MAX];
	Texture*			m_numTexture[NUM_MAX];
	float				m_time;
};