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

	//1フレームの経過時間を設定
	void SetFrameDeltaTime(float frameDeltaTime)
	{
		m_frameDeltaTime = min(1.0f / 10.0f, frameDeltaTime);
	}

	//1フレームの経過時間を取得
	float GetDeltaFrameTime()
	{
		return m_frameDeltaTime;
	}

private:
	float m_frameDeltaTime;		//1フレームの経過時間

};

static GameTime& GetGameTime()
{
	return GameTime::GetInstance();
}