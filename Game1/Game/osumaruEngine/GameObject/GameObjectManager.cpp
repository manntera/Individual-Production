#include "engineStdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "../Engine.h"


void GameObjectManager::Execute(LPDIRECT3DDEVICE9 pDevice)
{
	//������
	for (GameObject* object : m_objectVector)
	{
		object->Starter();
	}
	//�X�V
	for (GameObject* object : m_objectVector)
	{
		object->Updater();
	}

	GetShadowMap().Draw();
	//�`��
	// ��ʂ��N���A�B
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	pDevice->BeginScene();
	for (GameObject* object : m_objectVector)
	{
		object->Drawer();
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
	std::list<GameObject*>::iterator it = m_objectVector.begin();
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