#pragma once
#include "common.h"
#include "GameObject/GameObjectManager.h"
#include "Graphics\Sprite.h"
const int FRAME_BUFFER_WIDTH = 1280;
const int FRAME_BUFFER_HEIGHT = 720;

class EffectManager;
class GameObject;

class Engine
{
private:
	Engine();

	~Engine();
public:
	//DirectX‚ð‰Šú‰»
	void InitD3D(HINSTANCE& hInst);

	void GameLoop();

	LPDIRECT3D9& GetDirect3D()
	{
		return m_pD3D;
	}
	LPDIRECT3DDEVICE9& GetDevice()
	{
		return m_pD3DDevice;
	}

	EffectManager* GetEffectManager()
	{
		return m_effectManager;
	}

	static Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}

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
	template<class T> 
	T* New()
	{
		return m_objectManager.New<T>();
	}

	void Delete(GameObject* deleteObject)
	{
		m_objectManager.Delete(deleteObject);
	}

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;
	EffectManager*		m_effectManager;
	WNDCLASSEX			m_wc;
	GameObjectManager	m_objectManager;
};

static Engine& GetEngine()
{
	return Engine::GetEngine();
}

template <class T>
static inline T* New()
{
	return GetEngine().New<T>();
}

static inline void Delete(GameObject* deleteObject)
{
	GetEngine().Delete(deleteObject);
}