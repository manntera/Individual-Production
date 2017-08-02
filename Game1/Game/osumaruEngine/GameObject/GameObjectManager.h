#pragma once
#include "../common.h"

class GameObjectManager
{
public:
	//ゲームの1ループを実行する関数
	void Execute();

	//ゲームのオブジェクトを消去する関数
	void Delete(GameObject* deleteObject);

	//ゲームのオブジェクトを生成する
	template<class T>
	T* New();

private:
	//オブジェクトをリストから消去する関数
	void DeleteExecute();

private:
	std::vector<GameObject*> m_objectVector;

};