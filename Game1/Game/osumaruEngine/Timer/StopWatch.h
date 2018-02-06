#pragma once
//時間を計測するクラス

class StopWatch
{
public:

	//コンストラクタ
	StopWatch();

	//デストラクタ
	~StopWatch();

	//計測開始
	void Start();

	//計測終了
	void Stop();

	//経過時間を取得(単位は秒)
	double GetElapsedTime() const
	{
		return m_time;
	}

	double GetElapsedTimeMill() const
	{
		return m_millTime;
	}

private:
	LONGLONG m_start;			//スタート時の時間
	LONGLONG m_end;				//終了時の時間
	LONGLONG m_frequency;		//1秒を基準とした周波数
	double	m_time;				//経過時間(単位：秒)
	double	m_millTime;			//経過時間(単位：ミリ秒)
};