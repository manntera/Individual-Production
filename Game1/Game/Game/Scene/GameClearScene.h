#pragma once
//�Q�[���N���A�V�[���N���X

class GameClearScene : public GameObject
{
public:
	//�R���X�g���N�^
	GameClearScene();

	//�f�X�g���N�^
	~GameClearScene();

	void Init(float time);

	//�������֐�
	void Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;
private:
	float m_time;
	Sprite m_sprite;		//�Q�[���N���A�̃X�v���C�g
	static const int	NUM_MAX = 10;
	static const int	DIGIT_MAX = 2;
	static const int	TIME_MAX = 3;
	Sprite				m_timeSprite;
	Sprite				m_colonSprite[TIME_MAX];
	Sprite				m_numSprite[TIME_MAX][DIGIT_MAX];
	Texture*			m_numTexture[NUM_MAX];
};