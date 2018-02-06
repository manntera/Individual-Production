#include "engineStdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "../Engine.h"
#include "../Graphics/PostEffect/DepthOfField.h"

void GameObjectManager::Init()
{
	m_objectVector.resize(PRIORITY_MAX);
}

void GameObjectManager::Execute(PostEffect& postEffect)
{
	LPDIRECT3DDEVICE9 device = GetEngine().GetDevice();
	//初期化
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObjectData& object : objList)
		{
			object.gameObject->Starter();
		}
	}
	//更新
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObjectData& object : objList)
		{
			object.gameObject->Updater();
		}
	}

	GetShadowMap().Draw();
	//描画
	// 画面をクリア。
	device->SetRenderTarget(0, GetMainRenderTarget().GetRenderTarget());
	device->SetDepthStencilSurface(GetMainRenderTarget().GetDepthStencilBuffer());
	device->SetRenderTarget(1, GetDepthOfField().GetDepthRendertarget().GetRenderTarget());
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	////シーンの描画開始。
	device->BeginScene();
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObjectData& object : objList)
		{
			object.gameObject->Drawer();
		}
	}
	device->EndScene();

	device->SetRenderTarget(1, NULL);
	device->BeginScene();
	postEffect.Draw();
	GetPhysicsWorld().Draw();
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObjectData& object : objList)
		{
			object.gameObject->AfterDrawer();
		}
	}
	// シーンの描画終了。
	device->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	device->Present(NULL, NULL, NULL, NULL);

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
		std::list<GameObjectData>::iterator it = objList.begin();
		while (it != objList.end())
		{
			if ((*it).gameObject->IsDelete())
			{
				if ((*it).isNew)
				{
					GameObject *deleteObject = (*it).gameObject;
					delete deleteObject;
				}
				else
				{
					(*it).gameObject->Reset();
				}
				it = objList.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
	
}