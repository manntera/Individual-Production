#include "GameObjectManager.h"
#include "GameObject.h"

void GameObjectManager::Delete(GameObject* deleteObject)
{
	
}

template <class T>
T* GameObjectManager::New()
{
	T* newObject = new T;
	m_objectVector.push_back(newObject);
	return newObject;
}

void GameObjectManager::Execute()
{
	//更新
	for (GameObject* object : m_objectVector)
	{
		object->Update();
	}
	//描画
	for (GameObject* object : m_objectVector)
	{
		object->Render();
	}
	//最後にオブジェクトを消去
	DeleteExecute();
}

void GameObjectManager::DeleteExecute()
{
	std::vector<GameObject*>::iterator it = m_objectVector.begin();
	while (it != m_objectVector.end())
	{
		if ((*it)->IsDelete())
		{
			GameObject *deleteObject = *it;
			it = m_objectVector.erase(it);
			delete deleteObject;
		}
		else
		{
			it++;
		}
	}
	
}