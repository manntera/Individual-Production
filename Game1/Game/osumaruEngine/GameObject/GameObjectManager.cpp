#include "engineStdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "../Engine.h"


void GameObjectManager::Execute(LPDIRECT3DDEVICE9 pDevice)
{
	//������
	for (GameObject* object : m_objectVector)
	{
		if (!object->IsStart())
		{
			object->Start();
			object->FinishStart();
		}
	}
	//�X�V
	for (GameObject* object : m_objectVector)
	{
		object->Update();
	}
	LPDIRECT3DSURFACE9 renderTarget;
	LPDIRECT3DSURFACE9 shadowTarget;
	GetEngine().m_pShadowMap->GetSurfaceLevel(0, &shadowTarget);
	GetEngine().GetDevice()->GetRenderTarget(0, &renderTarget);

	GetEngine().GetDevice()->SetRenderTarget(0, shadowTarget);

	//�`��
	// ��ʂ��N���A�B
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	//pDevice->Present(NULL, NULL, NULL, NULL);
	//�V�[���̕`��J�n�B
	pDevice->BeginScene();
	for (GameObject* object : m_objectVector)
	{
		object->Render(0);
	}
	// �V�[���̕`��I���B
	pDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B

	GetEngine().GetDevice()->SetRenderTarget(0, renderTarget);
	//�`��
	// ��ʂ��N���A�B
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	pDevice->BeginScene();
	for (GameObject* object : m_objectVector)
	{
		object->Render(1);
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
	deleteObject->Delete();
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