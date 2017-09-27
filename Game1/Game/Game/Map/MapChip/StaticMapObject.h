#pragma once
#include "MapChip.h"

//背景オブジェクト

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

	//初期化関数
	void Start()override;

private:
	RigidBody		m_rigidBody;		//剛体
	MeshCollider	m_meshCollider;		//コライダー
};
