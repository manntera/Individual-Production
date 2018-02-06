#pragma once

class GameTime
{
	//コンストラクタ
	GameTime() :
		m_frameDeltaTime(1.0f / 60.0f)
	{
	}

	//デストラクタ
	~GameTime()
	{

	}
public:
	//インスタンスを取得
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
	float GetDeltaFrameTime() const
	{
		return m_frameDeltaTime;
	}

private:
	float m_frameDeltaTime;		//1フレームの経過時間

};

//ゲームタイマーを取得
static GameTime& GetGameTime()
{
	return GameTime::GetInstance();
}