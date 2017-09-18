#pragma once

class GameObject
{
public:
	//�R���X�g���N�^
	GameObject();

	//���z�f�X�g���N�^(���N���X�̃f�X�g���N�^�͉��z�֐��łȂ��Ă͂Ȃ�Ȃ��B)
	virtual ~GameObject();

	//�������֐�
	virtual void Start() {};

	//�X�V�֐�
	virtual void Update() = 0;

	//�`��֐�
	virtual void Render(int num) {};


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

	//���������I��������ɌĂԊ֐�
	void FinishStart()
	{
		m_isStart = true;
	}
	//�������ς݂��H
	bool IsStart()
	{
		return m_isStart;
	}

private:
	
	bool m_isDelete;	//�C���X�^���X���������Ɍ��Ă�t���O
	bool m_isStart;		//���������Ă邩�̃t���O
};