#pragma once
class GameObject;

class GameObjectManager
{
public:
	//�Q�[����1���[�v�����s����֐�
	void Execute(LPDIRECT3DDEVICE9 pDevice);

	//�Q�[���̃I�u�W�F�N�g����������֐�
	void Delete(GameObject* deleteObject)
	{

	}


	//�Q�[���̃I�u�W�F�N�g�𐶐�����
	template<class T>
	T* New()
	{
		T* newObject = new T;
		m_objectVector.push_back(newObject);
		return newObject;
	}

private:
	//�I�u�W�F�N�g�����X�g�����������֐�
	void DeleteExecute();

private:
	std::vector<GameObject*> m_objectVector;	//�I�u�W�F�N�g�̃��X�g

};