#include "engineStdafx.h"
#include "Physics.h"
#include "RigidBody.h"
#include "RigidBodyDraw.h"
#include "../Camera.h"

PhysicsWorld::PhysicsWorld()
{
	m_collisionConfig = NULL;
	m_collisionDispatcher = NULL;
	m_overlappingPairCache = NULL;
	m_constraintSolver = NULL;
	m_dynamicWorld = NULL;
	m_camera = nullptr;
}

PhysicsWorld::~PhysicsWorld()
{
	delete m_dynamicWorld;
	delete m_collisionConfig;
	delete m_collisionDispatcher;
	delete m_constraintSolver;
	delete m_overlappingPairCache;
	delete m_rigidBodyDraw;
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
	m_rigidBodyDraw = new RigidBodyDraw;
	m_rigidBodyDraw->Init();
	m_dynamicWorld->setDebugDrawer(m_rigidBodyDraw);
}

void PhysicsWorld::Update()
{
	m_dynamicWorld->stepSimulation(1.0f / 60.0f);
}

void PhysicsWorld::Draw()
{
	if (m_camera != nullptr)
	{
		m_rigidBodyDraw->Draw(m_camera->GetViewMatrix(), m_camera->GetProjectionMatrix());
	}
}

void PhysicsWorld::AddRigidBody(btRigidBody* rb)
{
	m_dynamicWorld->addRigidBody(rb);
}

void PhysicsWorld::RemoveRigidBody(btRigidBody* rb)
{
	m_dynamicWorld->removeRigidBody(rb);
}