#include "stdafx.h"
#include"GoalObject.h"


GoalObject::GoalObject() :
	m_multi(0.0f, 0.0f, 0.0f, 1.0f)
{
}

GoalObject::~GoalObject()
{

}

void GoalObject::Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);
	m_light.SetAmbiemtLight({ 70.0f, 70.0f, 1.0f, 1.0f });
	const float angle = 3.0f / 180.0f * cPI;
	D3DXQuaternionRotationAxis(&m_multi, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
	m_skinModel.SetShadowReceiverFlg(false);
}

void GoalObject::Update()
{
	MapChip::Update();
	if (!m_isActive)
	{
		return;
	}
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &m_multi);
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
