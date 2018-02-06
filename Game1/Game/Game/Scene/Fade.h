#pragma once
//フェードをするクラス

enum EnFadeState
{
	enFadeIn,
	enFadeOut,
};

class Fade : public GameObject
{
private:
	//コンストラクタ
	Fade();

	//デストラクタ
	~Fade();

public:

	//インスタンスを取得
	static Fade& GetInstance()
	{
		static Fade fade;
		return fade;
	}

	//初期化
	void Init();

	//フェードインする時に外部から呼び出す関数
	void FadeIn();

	//フェードアウトする時に外部から呼び出す関数
	void FadeOut();

	//更新関数
	void Update()override;

	//描画関数
	void AfterDraw()override;

	//フェードの状態を取得
	EnFadeState GetCurrentState() const
	{
		return m_state;
	}

	//フェード中か？
	bool IsExcute() const
	{
		return m_isExcute;
	}

private:
	const float	m_fadeTime;		//フェードする時間
	float		m_timer;		//タイマー
	Sprite		m_sprite;		//スプライト
	float		m_alpha;		//不透明度
	bool		m_isExcute;		//フェード中か？
	EnFadeState	m_state;		//フェードの状態
};

//フェードを取得
static Fade& GetFade()
{
	return Fade::GetInstance();
}