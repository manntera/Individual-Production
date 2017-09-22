#pragma once
#include "MapChip.h"

class StaticMapObject : public MapChip
{
public:
	/*
	初期化する関数
	position	座標
	rotation	回転
	modelName	読み込むモデルの名前
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName)override;


	void Start()override;

private:
	RigidBody		m_rigidBody;
	MeshCollider	m_meshCollider;
};
