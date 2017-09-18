#pragma once
#include "GameObject/GameObjectManager.h"
#include "Graphics\Sprite.h"
#include "Physics\Physics.h"
#include "Input\Pad.h"

//�G���W���N���X

const int FRAME_BUFFER_WIDTH = 1280;
const int FRAME_BUFFER_HEIGHT = 720;

class EffectManager;
class GameObject;


class Engine
{
private:
	//�R���X�g���N�^�B�V���O���g���̂��߃v���C�x�[�g�ɂȂ��Ă���
	Engine();

	//�f�X�g���N�^�B�V���O���g���̂��߃v���C�x�[�g�ɂȂ��Ă���
	~Engine();
public:
	//DirectX��������
	void InitD3D(HINSTANCE& hInst);

	//�Q�[�����[�v
	void GameLoop();

	//�_�C���N�g3D���擾
	LPDIRECT3D9& GetDirect3D()
	{
		return m_pD3D;
	}
	//�f�o�C�X���擾�B
	LPDIRECT3DDEVICE9& GetDevice()
	{
		return m_pD3DDevice;
	}
	//�G�t�F�N�g�}�l�[�W���[���擾
	EffectManager* GetEffectManager()
	{
		return m_effectManager;
	}
	//�������[���h���擾�B
	PhysicsWorld* GetPhysicsWorld()
	{
		return m_physicsWorld;
	}
	//�����̃C���X�^���X���擾
	static Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}
	//�����[�X
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
	//�C���X�^���X�̐���
	template<class T> 
	T* New()
	{
		return m_objectManager.New<T>();
	}
	//�C���X�^���X�̍폜
	void Delete(GameObject* deleteObject)
	{
		m_objectManager.Delete(deleteObject);
	}

	//�p�b�h�̎擾
	Pad& GetPad()
	{
		return m_pad;
	}

public:

	LPDIRECT3DTEXTURE9	m_pShadowMap;
private:


	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;			//�f�o�C�X
	EffectManager*		m_effectManager;		//�G�t�F�N�g�}�l�[�W���[
	WNDCLASSEX			m_wc;
	GameObjectManager	m_objectManager;		//�I�u�W�F�N�g�}�l�[�W���[
	PhysicsWorld*		m_physicsWorld;			//�������[���h
	Pad					m_pad;					//�p�b�h�̓��͂�
};
//�G���W���N���X�̃C���X�^���X���擾�B
static Engine& GetEngine()
{
	return Engine::GetEngine();
}

//�C���X�^���X�̐���
template <class T>
static T* New()
{
	return GetEngine().New<T>();
}
//�C���X�^���X�̍폜
static void Delete(GameObject* deleteObject)
{
	GetEngine().Delete(deleteObject);
}

//�p�b�h�̎擾
static Pad& GetPad()
{
	return GetEngine().GetPad();
}