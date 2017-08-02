#pragma once
#include "../common.h"

class GameObjectManager
{
public:
	//�Q�[����1���[�v�����s����֐�
	void Execute();

	//�Q�[���̃I�u�W�F�N�g����������֐�
	void Delete(GameObject* deleteObject);

	//�Q�[���̃I�u�W�F�N�g�𐶐�����
	template<class T>
	T* New();

private:
	//�I�u�W�F�N�g�����X�g�����������֐�
	void DeleteExecute();

private:
	std::vector<GameObject*> m_objectVector;

};