#pragma once
//�R���C�_�[�̊��N���X

class ICollider : Uncopyable
{
public:
	virtual btCollisionShape* GetBody() = 0;
};