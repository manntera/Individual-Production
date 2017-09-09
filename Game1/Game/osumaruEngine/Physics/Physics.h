#pragma once
class RigidBody;
/*
物理ワールド
*/

class PhysicsWorld
{
	btDefaultCollisionConfiguration*		collisionConfig;
	btCollisionDispatcher*					collisionDispatcher;		//衝突解決処理
	btBroadphaseInterface*					overlappingPairCache;		//ブロードフェーズ。
	btSequentialImpulseConstraintSolver*	constraintSolver;			//コンストレイントソルバー。拘束条件の解決処理
	btDiscreteDynamicsWorld*				dynamicWorld;				//ワールド
public:
	PhysicsWorld();

	~PhysicsWorld();

	void Init();

	void Update();

	//ダイナミックワールドを取得。
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
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
		dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
};