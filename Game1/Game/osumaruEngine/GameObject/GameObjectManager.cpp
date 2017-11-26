#include "engineStdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "../Engine.h"


void GameObjectManager::Init()
{
	m_objectVector.resize(priorityMax);
}

void GameObjectManager::Execute()
{
	LPDIRECT3DDEVICE9 pDevice = GetEngine().GetDevice();
	//������
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObject* object : objList)
		{
			object->Starter();
		}
	}
	//�X�V
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObject* object : objList)
		{
			object->Updater();
		}
	}

	GetShadowMap().Draw();
	//�`��
	// ��ʂ��N���A�B
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	pDevice->BeginScene();
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObject* object : objList)
		{
			object->Drawer();
		}
	}
	GetPhysicsWorld().Draw();
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObject* object : objList)
		{
			object->AfterDrawer();
		}
	}

	// �V�[���̕`��I���B
	pDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	pDevice->Present(NULL, NULL, NULL, NULL);

	//�Ō�ɃI�u�W�F�N�g������
	DeleteExecute();
}

void GameObjectManager::Delete(GameObject* deleteObject)
{
	deleteObject->BeforeDead();
	deleteObject->Dead();
}

void GameObjectManager::DeleteExecute()
{
	for (GameObjectList& objList : m_objectVector)
	{
		std::list<GameObject*>::iterator it = objList.begin();
		while (it != objList.end())
		{
			if ((*it)->IsDelete())
			{
				GameObject *deleteObject = *it;
				it = objList.erase(it);
				delete deleteObject;
			}
			else
			{
				it++;
			}
		}
	}
	
}