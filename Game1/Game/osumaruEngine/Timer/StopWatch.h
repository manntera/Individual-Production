#pragma once
//���Ԃ��v������N���X

class StopWatch
{
public:

	//�R���X�g���N�^
	StopWatch();

	//�f�X�g���N�^
	~StopWatch();

	//�v���J�n
	void Start();

	//�v���I��
	void Stop();

	//�o�ߎ��Ԃ��擾(�P�ʂ͕b)
	double GetElapsedTime()
	{
		return m_time;
	}

private:
	LONGLONG m_start;			//�X�^�[�g���̎���
	LONGLONG m_end;				//�I�����̎���
	LONGLONG m_frequency;		//1�b����Ƃ������g��
	double	m_time;				//�o�ߎ���
};