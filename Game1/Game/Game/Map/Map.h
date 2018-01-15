#pragma once
class MapChip;
class Player;
enum EnMapChipTag
{
	enMapTagUntagged,
	enMapTagPlayer,
	enMapTagFall,
	enMapTagGoal,
	enMapTagMapChip,
	enMapTagMoveFloor,
	enMapTagSpring,
	enMapTagRotation,
	enMapTagHindrance,
	enMapTagScoreUp,
	enMapTagNum,
};

//�}�b�v�̃I�u�W�F�N�g��z�u����N���X

class Map : public GameObject
{
public:
	//�R���X�g���N�^
	Map();

	//�f�X�g���N�^
	~Map();

	//������
	void Init(int stageNum);


	//�X�V�֐�
	void Update()override;

	//���ʑO�Ɉ�x�����Ă΂��
	void BeforeDead()override;

	//�v���C���[���擾
	Player* GetPlayer()
	{
		return m_player;
	}
	
	/*
	�}�b�v�`�b�v���f���[�g
	iterator	�f���[�g����}�b�v�`�b�v�̃C�e���[�^�[
	*/
	void MapChipErase(std::list<MapChip*>::iterator iterator);

private:
	std::list<MapChip*> m_mapChip;		//�}�b�v�`�b�v
	Player*	m_player;					//�v���C���[
	
};
