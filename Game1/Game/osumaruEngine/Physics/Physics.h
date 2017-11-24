#pragma once
class RigidBody;
class RigidBodyDraw;
class Camera;
/*
�������[���h
*/

class PhysicsWorld : Uncopyable
{
	btDefaultCollisionConfiguration*		m_collisionConfig;
	btCollisionDispatcher*					m_collisionDispatcher;		//�Փˉ�������
	btBroadphaseInterface*					m_overlappingPairCache;		//�u���[�h�t�F�[�Y�B
	btSequentialImpulseConstraintSolver*	m_constraintSolver;			//�R���X�g���C���g�\���o�[�B�S�������̉�������
	btDiscreteDynamicsWorld*				m_dynamicWorld;				//���[���h
	RigidBodyDraw*							m_rigidBodyDraw;
	Camera*									m_camera;
public:
	//�R���X�g���N�^
	PhysicsWorld();
	
	//�f�X�g���N�^
	~PhysicsWorld();

	//�������֐�
	void Init();

	//�X�V�֐�
	void Update();

	void Draw();

	//�_�C�i�~�b�N���[���h���擾�B
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return m_dynamicWorld;
	}
	//���̂𕨗����[���h�ɒǉ�
	void AddRigidBody(btRigidBody* rb);

	//���̂𕨗����[���h����폜
	void RemoveRigidBody(btRigidBody* rb);

	void SetCamera(Camera* camera)
	{
		m_camera = camera;
	}

	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f)
	{
		m_dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}

	void ContactTest(
		btCollisionObject* collisionObject,
		btCollisionWorld::ContactResultCallback& resultCallback)
	{
		m_dynamicWorld->contactTest(collisionObject, resultCallback);
	}

	void  DebugDraw(
		btTransform& worldTrans,
		btCollisionShape* colShape)
	{
		m_dynamicWorld->debugDrawObject(worldTrans, colShape, {1.0f, 0.0f, 0.0f});
	}
};