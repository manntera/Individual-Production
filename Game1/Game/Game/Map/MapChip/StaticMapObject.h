#pragma once
#include "MapChip.h"

class StaticMapObject : public MapChip
{
public:
	/*
	‰Šú‰»‚·‚éŠÖ”
	position	À•W
	rotation	‰ñ“]
	modelName	“Ç‚İ‚Şƒ‚ƒfƒ‹‚Ì–¼‘O
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName)override;


	void Start()override;

private:
	RigidBody		m_rigidBody;
	MeshCollider	m_meshCollider;
};
