#pragma once

class GameObject
{
public:
	//�R���X�g���N�^
	GameObject();

	//���z�f�X�g���N�^(���N���X�̃f�X�g���N�^�͉��z�֐��łȂ��Ă͂Ȃ�Ȃ��B)
	virtual ~GameObject();

	//����ł��邩�H
	bool IsDelete()
	{
		return m_isDelete;
	}

	//�����֐�
	void Delete()
	{
		m_isDelete = true;
	}

	//�X�V�֐�
	virtual void Update() = 0;

	//�`��֐�
	virtual void Render() {};

private:
	//�C���X�^���X���������Ɍ��Ă�t���O
	bool m_isDelete;
};