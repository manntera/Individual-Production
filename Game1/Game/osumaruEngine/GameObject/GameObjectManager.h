#pragma once
class GameObject;

const int priorityMax = 16;
class GameObjectManager : Uncopyable
{
public:

	//初期化関数
	void Init();

	//ゲームの1ループを実行する関数
	void Execute();

	//ゲームのオブジェクトを消去する関数
	void Delete(GameObject* deleteObject);


	//ゲームのオブジェクトを生成する
	template<class T>
	T* New(int priority)
	{
		if (priority < 0 || priorityMax <= priority)
		{
			return nullptr;
		}
		T* newObject = new T;
		m_objectVector[priority].push_back(newObject);
		return newObject;
	}

private:
	//オブジェクトをリストから消去する関数
	void DeleteExecute();

private:
	typedef std::list<GameObject*> GameObjectList;	//オブジェクトのリスト
	std::vector<GameObjectList> m_objectVector;
};