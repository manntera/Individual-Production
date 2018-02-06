#pragma once
//オブジェクトのインターフェース

class GameObject : Uncopyable
{
public:
	//コンストラクタ
	GameObject();

	//仮想デストラクタ(基底クラスのデストラクタは仮想関数でなくてはならない。)
	virtual ~GameObject();

	//初期化関数
	virtual bool Start() { return true; }

	//更新関数
	virtual void Update() = 0;

	//描画関数
	virtual void Draw() {};

	//Drawを呼び終わった後にもう一度呼ぶ関数。アルファブレンドしたいスプライトやポストエフェクトを切ってスプライトを描画したいときに使う。
	virtual void AfterDraw() {};

	//死ぬ前に一回だけ呼ばれる関数
	virtual void BeforeDead() {};

	void Reset()
	{
		m_isStart = false;
		m_isDelete = false;
	}

	//死んでいるか？
	bool IsDelete() const
	{
		return m_isDelete;
	}
	//初期化済みか？
	bool IsStart() const
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
			m_isStart = Start();
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
	bool m_isDelete;			//インスタンスを消す時に建てるフラグ
	bool m_isStart;				//初期化してるかのフラグ
};