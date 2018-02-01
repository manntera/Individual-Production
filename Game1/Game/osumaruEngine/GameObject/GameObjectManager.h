#pragma once
class GameObject;
#include "../Graphics/PostEffect/PostEffect.h"

struct GameObjectData
{
	GameObject* gameObject;		//オブジェクト
	bool isNew;					//このオブジェクトがnewされて作ったか否か
};
const int PRIORITY_MAX = 16;

class GameObjectManager : Uncopyable
{
public:

	//初期化関数
	void Init();

	//ゲームの1ループを実行する関数
	void Execute(PostEffect& postEffect);

	//ゲームのオブジェクトを消去する関数
	void Delete(GameObject* deleteObject);


	//ゲームのオブジェクトを生成する
	template<class T>
	T* New(int priority)
	{
		if (priority < 0 || PRIORITY_MAX <= priority)
		{
			return nullptr;
		}
		T* newObject = new T;
		m_objectVector[priority].push_back({ newObject, true });
		return newObject;
	}

	void Add(GameObject* object, int priority)
	{
		m_objectVector[priority].push_back({ object, false });
	}



private:
	//オブジェクトをリストから消去する関数
	void DeleteExecute();

private:
	typedef std::list<GameObjectData> GameObjectList;	//オブジェクトのリスト
	std::vector<GameObjectList> m_objectVector;		//オブジェクト
};