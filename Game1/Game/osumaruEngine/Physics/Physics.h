#pragma once
class RigidBody;
/*
�������[���h
*/

class PhysicsWorld
{
	btDefaultCollisionConfiguration*		collisionConfig;
	btCollisionDispatcher*					collisionDispatcher;		//�Փˉ�������
	btBroadphaseInterface*					overlappingPairCache;		//�u���[�h�t�F�[�Y�B
	btSequentialImpulseConstraintSolver*	constraintSolver;			//�R���X�g���C���g�\���o�[�B�S�������̉�������
	btDiscreteDynamicsWorld*				dynamicWorld;				//���[���h
public:
	PhysicsWorld();

	~PhysicsWorld();

	void Init();

	void Update();

	//�_�C�i�~�b�N���[���h���擾�B
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	//���̂𕨗����[���h�ɒǉ�
	void AddRigidBody(btRigidBody* rb);

	//���̂𕨗����[���h����폜
	void RemoveRigidBody(btRigidBody* rb);

	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f)
	{
		dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
};