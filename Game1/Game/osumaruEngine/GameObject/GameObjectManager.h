#pragma once
class GameObject;

class GameObjectManager
{
public:
	//ゲームの1ループを実行する関数
	void Execute(LPDIRECT3DDEVICE9 pDevice);

	//ゲームのオブジェクトを消去する関数
	void Delete(GameObject* deleteObject)
	{

	}


	//ゲームのオブジェクトを生成する
	template<class T>
	T* New()
	{
		T* newObject = new T;
		m_objectVector.push_back(newObject);
		return newObject;
	}

private:
	//オブジェクトをリストから消去する関数
	void DeleteExecute();

private:
	std::vector<GameObject*> m_objectVector;	//オブジェクトのリスト

};