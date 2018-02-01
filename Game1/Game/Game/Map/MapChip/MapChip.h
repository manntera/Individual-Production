#pragma once
//�}�b�v�Ŕz�u����I�u�W�F�N�g�̊��N���X
class Map;


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
	anim		�A�j���[�V�����t���̃��f���̏ꍇ�A�j���[�V������������ꕨ
	*/
	virtual void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim = nullptr);

	//�������֐�
	virtual bool Start()override;

	//�X�V�֐�
	virtual void Update()override;

	//�`��֐�
	virtual void Draw()override;

	D3DXMATRIX GetWorldMatrix()
	{
		return m_skinModel.GetWorldMatrix();
	}
	
	/*
	�C�e���[�^�[���Z�b�g
	map			���g���f���[�g���邽�߂̃C���X�^���X
	iterator	���g�̃C�e���[�^�[
	*/
	void SetIterator(Map* map, std::list<MapChip*>::iterator iterator);

	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

protected:
	//�f���[�g����֐�
	void MapChipDelete();

protected:

	SkinModelData	m_skinModelData;			//�X�L�������f���f�[�^
	SkinModel		m_skinModel;				//�X�L�����f��
	Light			m_light;					//���f���̃��C�g
	D3DXVECTOR3		m_position;					//���W
	D3DXQUATERNION	m_rotation;					//��]
	D3DXVECTOR3		m_scale;					//�g��
	Map*			m_pMap;						//�f���[�g���鎞�̂��߂̃|�C���^
	std::list<MapChip*>::iterator m_iterator;	//���g�̃C�e���[�^�[
	bool			m_isActive;					//�A�N�e�B�u���H
};