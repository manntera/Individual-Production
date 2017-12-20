#pragma once

class GameTime
{
	GameTime()
	{
		m_frameDeltaTime = 1.0f / 60.0f;
	}

	~GameTime()
	{

	}
public:
	static GameTime& GetInstance()
	{
		static GameTime gametime;
		return gametime;
	}

	//1�t���[���̌o�ߎ��Ԃ�ݒ�
	void SetFrameDeltaTime(float frameDeltaTime)
	{
		m_frameDeltaTime = min(1.0f / 10.0f, frameDeltaTime);
	}

	//1�t���[���̌o�ߎ��Ԃ��擾
	float GetDeltaFrameTime()
	{
		return m_frameDeltaTime;
	}

private:
	float m_frameDeltaTime;		//1�t���[���̌o�ߎ���

};

static GameTime& GetGameTime()
{
	return GameTime::GetInstance();
}