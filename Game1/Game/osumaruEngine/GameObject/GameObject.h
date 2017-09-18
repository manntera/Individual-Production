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
	virtual void Render(int num) {};


	//死んでいるか？
	bool IsDelete()
	{
		return m_isDelete;
	}

	//消去関数
	void Delete()
	{
		m_isDelete = true;
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

private:
	
	bool m_isDelete;	//インスタンスを消す時に建てるフラグ
	bool m_isStart;		//初期化してるかのフラグ
};