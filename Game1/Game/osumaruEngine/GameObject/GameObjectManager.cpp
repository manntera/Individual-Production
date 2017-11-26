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
	//初期化
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObject* object : objList)
		{
			object->Starter();
		}
	}
	//更新
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObject* object : objList)
		{
			object->Updater();
		}
	}

	GetShadowMap().Draw();
	//描画
	// 画面をクリア。
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
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

	// シーンの描画終了。
	pDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	pDevice->Present(NULL, NULL, NULL, NULL);

	//最後にオブジェクトを消去
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