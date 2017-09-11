#include "engineStdafx.h"
#include "Physics.h"
#include "RigidBody.h"

PhysicsWorld::PhysicsWorld()
{
	m_collisionConfig = NULL;
	m_collisionDispatcher = NULL;
	m_overlappingPairCache = NULL;
	m_constraintSolver = NULL;
	m_dynamicWorld = NULL;
}

PhysicsWorld::~PhysicsWorld()
{
	delete m_dynamicWorld;
	delete m_collisionConfig;
	delete m_collisionDispatcher;
	delete m_constraintSolver;
	delete m_overlappingPairCache;
}


void PhysicsWorld::Init()
{
	//•¨—ƒGƒ“ƒWƒ“‚ð‰Šú‰»
	m_collisionConfig = new btDefaultCollisionConfiguration;
	m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfig);
	m_overlappingPairCache = new btDbvtBroadphase();
	m_constraintSolver = new btSequentialImpulseConstraintSolver();

	m_dynamicWorld = new btDiscreteDynamicsWorld(
		m_collisionDispatcher,
		m_overlappingPairCache,
		m_constraintSolver,
		m_collisionConfig
		);
	m_dynamicWorld->setGravity(btVector3(0, -10, 0));
}

void PhysicsWorld::Update()
{
	m_dynamicWorld->stepSimulation(1.0f / 60.0f);
}

void PhysicsWorld::AddRigidBody(btRigidBody* rb)
{
	m_dynamicWorld->addRigidBody(rb);
}

void PhysicsWorld::RemoveRigidBody(btRigidBody* rb)
{
	m_dynamicWorld->removeRigidBody(rb);
}