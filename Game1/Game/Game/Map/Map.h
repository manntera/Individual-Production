#pragma once
class MapChip;
class Player;
//�}�b�v�`�b�v�̃^�O
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
	enMapTagStopTime,
	enMapTagGoalObject,
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
	const Player* GetPlayer() const
	{
		return m_player;
	}
	
	/*
	�}�b�v�`�b�v���f���[�g
	iterator	�f���[�g����}�b�v�`�b�v�̃C�e���[�^�[
	*/
	void MapChipErase(std::list<MapChip*>::iterator iterator);

	//���Ԃ��~�߂�֐�
	void StopTime();

private:
	std::list<MapChip*> m_mapChip;					//�}�b�v�`�b�v
	Player*				m_player;					//�v���C���[
	float				m_stopTime;					//�X�e�[�W�M�~�b�N���~�߂Ă�Ԃ̃J�E���^�[
	bool				m_isLoad;					//���f���̓ǂݍ��߂����̃t���O
};
