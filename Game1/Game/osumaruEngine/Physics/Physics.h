#pragma once
class RigidBody;
/*
物理ワールド
*/

class PhysicsWorld
{
	btDefaultCollisionConfiguration*		m_collisionConfig;
	btCollisionDispatcher*					m_collisionDispatcher;		//衝突解決処理
	btBroadphaseInterface*					m_overlappingPairCache;		//ブロードフェーズ。
	btSequentialImpulseConstraintSolver*	m_constraintSolver;			//コンストレイントソルバー。拘束条件の解決処理
	btDiscreteDynamicsWorld*				m_dynamicWorld;				//ワールド
public:
	//コンストラクタ
	PhysicsWorld();
	
	//デストラクタ
	~PhysicsWorld();

	//初期化関数
	void Init();

	//更新関数
	void Update();

	//ダイナミックワールドを取得。
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return m_dynamicWorld;
	}
	//剛体を物理ワールドに追加
	void AddRigidBody(btRigidBody* rb);

	//剛体を物理ワールドから削除
	void RemoveRigidBody(btRigidBody* rb);

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
		m_dynamicWorld->debugDrawObject(worldTrans, colShape, {0.0f, 0.0f, 1.0f});
	}
};