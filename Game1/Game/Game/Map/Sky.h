#pragma once
//��̃N���X

class Sky : public GameObject
{
public:

	//�R���X�g���N�^
	Sky();

	//�f�X�g���N�^
	~Sky();

	//�������֐�
	void Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;
private:

	SkinModel		m_skinModel;			//�X�L�����f��
	SkinModelData	m_skinModelData;		//�X�L�����f���f�[�^
	Light			m_light;				//���f���̃��C�g
};