#pragma once

class GameObject
{
public:
	//コンストラクタ
	GameObject();

	//仮想デストラクタ(基底クラスのデストラクタは仮想関数でなくてはならない。)
	virtual ~GameObject();

	//初期化関数
	virtual void Start() {};

	//更新関数
	virtual void Update() = 0;

	//描画関数
	virtual void Draw() {};

	//死ぬ前に一回だけ呼ばれる関数
	virtual void BeforeDead() {};

	//死んでいるか？
	bool IsDelete()
	{
		return m_isDelete;
	}

	//初期化が終わった時に呼ぶ関数
	void FinishStart()
	{
		m_isStart = true;
	}
	//初期化済みか？
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
private:
	
	bool m_isDelete;	//インスタンスを消す時に建てるフラグ
	bool m_isStart;		//初期化してるかのフラグ
};