#pragma once
class MapChip;
class Player;

//�}�b�v�̃I�u�W�F�N�g��z�u����N���X

class Map : public GameObject
{
public:
	//�R���X�g���N�^
	Map();

	//�f�X�g���N�^
	~Map();

	//������
	void Init();

	//�������֐�
	void Start()override;

	//�X�V�֐�
	void Update()override;

	//���ʑO�Ɉ�x�����Ă΂��
	void BeforeDead()override;

	//�v���C���[���擾
	Player* GetPlayer()
	{
		return m_player;
	}

private:
	std::vector<MapChip*> m_mapChip;
	Player*	m_player;
	
};
