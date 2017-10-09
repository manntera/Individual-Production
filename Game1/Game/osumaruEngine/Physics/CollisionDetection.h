#pragma once
#include "RigidBody.h"

class CollisionDetection
{
public:

	CollisionDetection();

	~CollisionDetection();


	void Init(ICollider* collider, D3DXVECTOR3 position, D3DXQUATERNION rotation);

	void SetPosition(D3DXVECTOR3 position)
	{
		m_position = position;
		m_rigidBody.GetBody()->getWorldTransform().setOrigin({ position.x, position.y, position.z });
	}

	void SetRotation(D3DXQUATERNION rotation)
	{
		m_rotation = rotation;
		m_rigidBody.GetBody()->getWorldTransform().setRotation({ m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w });
	}

	void Execute();

	bool IsHit()
	{
		return m_isHit;
	}

	void SetUserIndex(int userIndex)
	{
		m_rigidBody.GetBody()->setUserIndex(userIndex);
	}

	void Draw();
private:
	RigidBody		m_rigidBody;
	ICollider*		m_pCollider;
	D3DXVECTOR3		m_position;
	D3DXQUATERNION	m_rotation;
	bool			m_isHit;
};