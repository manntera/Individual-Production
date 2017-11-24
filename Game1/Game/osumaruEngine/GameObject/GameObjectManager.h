#pragma once
class GameObject;

const int priorityMax = 16;
class GameObjectManager : Uncopyable
{
public:

	//�������֐�
	void Init();

	//�Q�[����1���[�v�����s����֐�
	void Execute();

	//�Q�[���̃I�u�W�F�N�g����������֐�
	void Delete(GameObject* deleteObject);


	//�Q�[���̃I�u�W�F�N�g�𐶐�����
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
	//�I�u�W�F�N�g�����X�g�����������֐�
	void DeleteExecute();

private:
	typedef std::list<GameObject*> GameObjectList;	//�I�u�W�F�N�g�̃��X�g
	std::vector<GameObjectList> m_objectVector;
};