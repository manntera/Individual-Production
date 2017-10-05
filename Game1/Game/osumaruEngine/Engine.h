#pragma once
#include "GameObject/GameObjectManager.h"
#include "Graphics\Sprite.h"
#include "Physics\Physics.h"
#include "Input\Pad.h"
#include "Graphics\ShadowMap.h"

//エンジンクラス

const int FRAME_BUFFER_WIDTH = 1280;
const int FRAME_BUFFER_HEIGHT = 720;

class EffectManager;
class GameObject;


class Engine
{
private:
	//コンストラクタ。シングルトンのためプライベートになっている
	Engine();

	//デストラクタ。シングルトンのためプライベートになっている
	~Engine();
public:
	//DirectXを初期化
	void InitD3D(HINSTANCE& hInst);

	//ゲームループ
	void GameLoop();

	//ダイレクト3Dを取得
	LPDIRECT3D9& GetDirect3D()
	{
		return m_pD3D;
	}
	//デバイスを取得。
	LPDIRECT3DDEVICE9& GetDevice()
	{
		return m_pD3DDevice;
	}
	//エフェクトマネージャーを取得
	EffectManager* GetEffectManager()
	{
		return m_effectManager;
	}
	//物理ワールドを取得。
	PhysicsWorld* GetPhysicsWorld()
	{
		return m_physicsWorld;
	}

	//シャドウマップを取得
	ShadowMap& GetShadowMap()
	{
		return m_shadowMap;
	}
	//自分のインスタンスを取得
	static Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}
	//リリース
	void Release()
	{
		if (m_pD3DDevice != NULL)
		{
			m_pD3DDevice->Release();
		}
		if (m_pD3D != NULL)
		{
			m_pD3D->Release();
		}
		PostQuitMessage(0);
	}
	//インスタンスの生成
	template<class T> 
	T* New(int priority)
	{
		return m_objectManager.New<T>(priority);
	}
	//インスタンスの削除
	void Delete(GameObject* deleteObject)
	{
		m_objectManager.Delete(deleteObject);
	}

	//パッドの取得
	Pad& GetPad()
	{
		return m_pad;
	}
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;			//デバイス
	EffectManager*		m_effectManager;		//エフェクトマネージャー
	WNDCLASSEX			m_wc;
	GameObjectManager	m_objectManager;		//オブジェクトマネージャー
	PhysicsWorld*		m_physicsWorld;			//物理ワールド
	Pad					m_pad;					//パッドの入力
	ShadowMap			m_shadowMap;			//シャドウマップ
};
//エンジンクラスのインスタンスを取得。
static Engine& GetEngine()
{
	return Engine::GetEngine();
}

//インスタンスの生成
template <class T>
static T* New(int priority)
{
	return GetEngine().New<T>(priority);
}
//インスタンスの削除
static void Delete(GameObject* deleteObject)
{
	GetEngine().Delete(deleteObject);
}

//パッドの取得
static Pad& GetPad()
{
	return GetEngine().GetPad();
}

static ShadowMap& GetShadowMap()
{
	return GetEngine().GetShadowMap();
}