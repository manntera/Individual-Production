#pragma once
class RigidBody;
class RigidBodyDraw;
class Camera;
/*
物理ワールド
*/

class PhysicsWorld : Uncopyable
{
	btDefaultCollisionConfiguration*		m_collisionConfig;
	btCollisionDispatcher*					m_collisionDispatcher;		//衝突解決処理
	btBroadphaseInterface*					m_overlappingPairCache;		//ブロードフェーズ。
	btSequentialImpulseConstraintSolver*	m_constraintSolver;			//コンストレイントソルバー。拘束条件の解決処理
	btDiscreteDynamicsWorld*				m_dynamicWorld;				//ワールド
	RigidBodyDraw*							m_rigidBodyDraw;
	Camera*									m_camera;
public:
	//コンストラクタ
	PhysicsWorld();
	
	//デストラクタ
	~PhysicsWorld();

	//初期化関数
	void Init();

	//更新関数
	void Update();

	void Draw();

	//ダイナミックワールドを取得。
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return m_dynamicWorld;
	}
	//剛体を物理ワールドに追加
	void AddRigidBody(btRigidBody* rb);

	//剛体を物理ワールドから削除
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