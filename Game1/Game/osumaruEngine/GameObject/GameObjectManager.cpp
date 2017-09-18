#include "engineStdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "../Engine.h"


void GameObjectManager::Execute(LPDIRECT3DDEVICE9 pDevice)
{
	//初期化
	for (GameObject* object : m_objectVector)
	{
		if (!object->IsStart())
		{
			object->Start();
			object->FinishStart();
		}
	}
	//更新
	for (GameObject* object : m_objectVector)
	{
		object->Update();
	}
	LPDIRECT3DSURFACE9 renderTarget;
	LPDIRECT3DSURFACE9 shadowTarget;
	GetEngine().m_pShadowMap->GetSurfaceLevel(0, &shadowTarget);
	GetEngine().GetDevice()->GetRenderTarget(0, &renderTarget);

	GetEngine().GetDevice()->SetRenderTarget(0, shadowTarget);

	//描画
	// 画面をクリア。
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	//pDevice->Present(NULL, NULL, NULL, NULL);
	//シーンの描画開始。
	pDevice->BeginScene();
	for (GameObject* object : m_objectVector)
	{
		object->Render(0);
	}
	// シーンの描画終了。
	pDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。

	GetEngine().GetDevice()->SetRenderTarget(0, renderTarget);
	//描画
	// 画面をクリア。
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	pDevice->BeginScene();
	for (GameObject* object : m_objectVector)
	{
		object->Render(1);
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