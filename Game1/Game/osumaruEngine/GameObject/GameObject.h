#pragma once

class GameObject
{
public:
	GameObject();
	//仮想デストラクタ(基底クラスのデストラクタは仮想関数でなくてはならない。)
	virtual ~GameObject();

	bool IsDelete()
	{
		return m_isDelete;
	}

	void Delete()
	{
		m_isDelete = true;
	}
//protected:
	//更新関数
	virtual void Update() = 0;
	//描画関数
	virtual void Render() {};

private:
	//インスタンスを消す時に建てるフラグ
	bool m_isDelete;
};