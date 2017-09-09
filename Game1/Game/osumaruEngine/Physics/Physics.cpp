#include "engineStdafx.h"
#include "Physics.h"
#include "RigidBody.h"

PhysicsWorld::PhysicsWorld()
{
	collisionConfig = NULL;
	collisionDispatcher = NULL;
	overlappingPairCache = NULL;
	constraintSolver = NULL;
	dynamicWorld = NULL;
}

PhysicsWorld::~PhysicsWorld()
{
	delete dynamicWorld;
	delete collisionConfig;
	delete collisionDispatcher;
	delete constraintSolver;
	delete overlappingPairCache;
}


void PhysicsWorld::Init()
{
	//•¨—ƒGƒ“ƒWƒ“‚ð‰Šú‰»
	collisionConfig = new btDefaultCollisionConfiguration;
	collisionDispatcher = new btCollisionDispatcher(collisionConfig);
	overlappingPairCache = new btDbvtBroadphase();
	constraintSolver = new btSequentialImpulseConstraintSolver();

	dynamicWorld = new btDiscreteDynamicsWorld(
		collisionDispatcher,
		overlappingPairCache,
		constraintSolver,
		collisionConfig
		);
	dynamicWorld->setGravity(btVector3(0, -10, 0));
}

void PhysicsWorld::Update()
{
	dynamicWorld->stepSimulation(1.0f / 60.0f);
}

void PhysicsWorld::AddRigidBody(btRigidBody* rb)
{
	dynamicWorld->addRigidBody(rb);
}

void PhysicsWorld::RemoveRigidBody(btRigidBody* rb)
{
	dynamicWorld->removeRigidBody(rb);
}