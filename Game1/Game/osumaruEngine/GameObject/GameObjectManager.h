#pragma once
class GameObject;
#include "../Graphics/PostEffect/PostEffect.h"

struct GameObjectData
{
	GameObject* gameObject;		//�I�u�W�F�N�g
	bool isNew;					//���̃I�u�W�F�N�g��new����č�������ۂ�
};
const int PRIORITY_MAX = 16;

class GameObjectManager : Uncopyable
{
public:

	//�������֐�
	void Init();

	//�Q�[����1���[�v�����s����֐�
	void Execute(PostEffect& postEffect);

	//�Q�[���̃I�u�W�F�N�g����������֐�
	void Delete(GameObject* deleteObject);


	//�Q�[���̃I�u�W�F�N�g�𐶐�����
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
	//�I�u�W�F�N�g�����X�g�����������֐�
	void DeleteExecute();

private:
	typedef std::list<GameObjectData> GameObjectList;	//�I�u�W�F�N�g�̃��X�g
	std::vector<GameObjectList> m_objectVector;		//�I�u�W�F�N�g
};