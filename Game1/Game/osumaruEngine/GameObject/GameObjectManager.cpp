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
	//�X�V
	for (GameObject* object : m_objectVector)
	{
		object->Update();
	}
	//�`��
	for (GameObject* object : m_objectVector)
	{
		object->Render();
	}
	//�Ō�ɃI�u�W�F�N�g������
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