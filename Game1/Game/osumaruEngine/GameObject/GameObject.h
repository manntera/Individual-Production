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
	virtual void Draw() {};

	//Draw���ĂяI�������ɂ�����x�ĂԊ֐��B�A���t�@�u�����h�������X�v���C�g��|�X�g�G�t�F�N�g��؂��ăX�v���C�g��`�悵�����Ƃ��Ɏg���B
	virtual void AfterDraw() {};

	//���ʑO�Ɉ�񂾂��Ă΂��֐�
	virtual void BeforeDead() {};

	//����ł��邩�H
	bool IsDelete()
	{
		return m_isDelete;
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


	void Dead()
	{
		m_isDelete = true;
	}

	void Starter()
	{
		if (!m_isStart && !m_isDelete)
		{
			Start();
			m_isStart = true;
		}
	}

	void Updater()
	{
		if (m_isStart && !m_isDelete)
		{
			Update();
		}
	}

	void Drawer()
	{
		if (m_isStart && !m_isDelete)
		{
			Draw();
		}
	}

	void AfterDrawer()
	{
		if (m_isStart && !m_isDelete)
		{
			AfterDraw();
		}
	}
private:
	
	bool m_isDelete;	//�C���X�^���X���������Ɍ��Ă�t���O
	bool m_isStart;		//���������Ă邩�̃t���O
};