#pragma once
class GameObject;
#include "../Graphics/PostEffect/PostEffect.h"
//オブジェクトマネージャー

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


	/*
	オブジェクトを生成する。
	priority	オブジェクトの優先度
	*/
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

	/*
	オブジェクトを登録
	object		登録するオブジェクト
	priority	オブジェクトの優先度
	ret			オブジェクトの登録に成功したか？
	*/
	bool Add(GameObject* object, int priority)
	{
		if (priority < 0 || PRIORITY_MAX <= priority)
		{
			return false;
		}
		m_objectVector[priority].push_back({ object, false });
		return true;
	}



private:
	//オブジェクトをリストから消去する関数
	void DeleteExecute();

private:
	typedef std::list<GameObjectData> GameObjectList;	//オブジェクトのリスト
	std::vector<GameObjectList> m_objectVector;		//オブジェクト
};