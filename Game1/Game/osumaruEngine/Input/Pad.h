#pragma once
//パッドの入力を取得するクラス

enum EnPadButton
{
	enButtonUp,
	enButtonDown,
	enButtonLeft,
	enButtonRight,
	enButtonA,
	enButtonB,
	enButtonX,
	enButtonY,
	enButtonSelect,
	enButtonStart,
	enButtonRB,
	enButtonRStickPush,
	enButtonLB,
	enButtonLStickPush,
	enButtonNum,

};

class Pad
{
public:

	//コンストラクタ
	Pad();

	//デストラクタ
	~Pad();

	//更新
	void Update();

	/*
	ボタンを押しているか調べる関数
	button			押されているか調べたいボタンのenum
	*/
	bool IsTriggerButton(EnPadButton button)
	{
		return m_isPadTrigger[button];
	}

	/*
	ボタンを押しているか調べる関数
	button			押されているか調べたいボタンのenum
	*/
	bool IsPressButton(EnPadButton button)
	{
		return m_isPadPress[button];
	}

	//左スティックのX軸の入力量を取得(-1.0から1.0の間
	float GetLeftStickX()
	{
		return m_leftStickX;
	}

	//左スティックのY軸の入力量を取得(-1.0から1.0の間
	float GetLeftStickY()
	{
		return m_leftStickY;
	}

	//右スティックのX軸の入力量を取得(-1.0から1.0の間
	float GetRightStickX()
	{
		return m_rightStickX;
	}

	//右スティックのY軸の入力量を取得(-1.0から1.0の間
	float GetRightStickY()
	{
		return m_rightStickY;
	}

	//パッドの左のトリガーの入力量を取得(0.0から1.0
	float GetLeftTrigger()
	{
		return m_leftTrigger;
	}
	//パッドの右のトリガーの入力量を取得(0.0から1.0
	float GetRightTrigger()
	{
		return m_rightTrigger;
	}

private:
	int				m_padNum;						//パッドの番号
	float			m_rightStickX;					//右スティックのX軸の入力量
	float			m_rightStickY;					//右スティックのY軸の入力量
	float			m_leftStickX;					//左スティックのX軸の入力量
	float			m_leftStickY;					//左スティックのY軸の入力量
	float			m_rightTrigger;					//右トリガーの入力量
	float			m_leftTrigger;					//左トリガーの入力量
	bool			m_isPadPress[enButtonNum];		//各ボタンが押されているか？
	bool			m_isPadTrigger[enButtonNum];	//各ボタンが押されているか？(トリガー)
	XINPUT_STATE	m_state;						//パッドの入力状態
};