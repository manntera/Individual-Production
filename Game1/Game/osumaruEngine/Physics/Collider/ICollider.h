#pragma once
//�R���C�_�[�̊��N���X

class ICollider
{
public:
	virtual btCollisionShape* GetBody() = 0;
};