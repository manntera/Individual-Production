#pragma once
//�}�b�v�Ŕz�u����I�u�W�F�N�g�̊��N���X

class MapChip : public GameObject
{
public:

	//�R���X�g���N�^
	MapChip();

	//�f�X�g���N�^
	virtual ~MapChip();

	/*
	����������֐�
	position	���W
	rotation	��]
	modelName	�ǂݍ��ރ��f���̖��O
	*/
	virtual void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName);

	//�������֐�
	virtual void Start()override;

	//�X�V�֐�
	virtual void Update()override;

	//�`��֐�
	virtual void Draw()override;


protected:
	SkinModelData	m_skinModelData;	//�X�L�������f���f�[�^
	SkinModel		m_skinModel;		//�X�L�����f��
	Light			m_light;			//���f���̃��C�g
	D3DXVECTOR3		m_position;			//���W
	D3DXQUATERNION	m_rotation;			//��]
};