#include "engineStdafx.h"
#include "Physics.h"
#include "RigidBody.h"
#include "RigidBodyDraw.h"
#include "../Camera.h"

PhysicsWorld::PhysicsWorld() :
	m_pCollisionConfig(nullptr),
	m_pCollisionDispatcher(nullptr),
	m_pOverlappingPairCache(nullptr),
	m_pConstraintSolver(nullptr),
	m_pDynamicWorld(nullptr),
	m_pRigidBodyDraw(nullptr),
	m_pCamera(nullptr)
{
}

PhysicsWorld::~PhysicsWorld()
{
}


void PhysicsWorld::Init()
{
	//•¨—ƒGƒ“ƒWƒ“‚ð‰Šú‰»
	m_pCollisionConfig.reset(new btDefaultCollisionConfiguration);
	m_pCollisionDispatcher.reset(new btCollisionDispatcher(m_pCollisionConfig.get()));
	m_pOverlappingPairCache.reset(new btDbvtBroadphase());
	m_pConstraintSolver.reset(new btSequentialImpulseConstraintSolver());

	m_pDynamicWorld.reset(new btDiscreteDynamicsWorld(
		m_pCollisionDispatcher.get(),
		m_pOverlappingPairCache.get(),
		m_pConstraintSolver.get(),
		m_pCollisionConfig.get()
		));
	m_pDynamicWorld->setGravity(btVector3(0, -10, 0));
	m_pRigidBodyDraw.reset(new RigidBodyDraw);
	m_pRigidBodyDraw->Init();
	m_pDynamicWorld->setDebugDrawer(m_pRigidBodyDraw.get());
}

void PhysicsWorld::Update()
{
	m_pDynamicWorld->stepSimulation(GetGameTime().GetDeltaFrameTime());
}

void PhysicsWorld::Draw()
{
	if (m_pCamera != nullptr)
	{
		//m_pRigidBodyDraw->Draw(m_pCamera->GetViewMatrix(), m_pCamera->GetProjectionMatrix());
		m_pRigidBodyDraw->Reset();
	}
}

void PhysicsWorld::AddRigidBody(btRigidBody* rb)
{
	m_pDynamicWorld->addRigidBody(rb);
}

void PhysicsWorld::RemoveRigidBody(btRigidBody* rb)
{
	m_pDynamicWorld->removeRigidBody(rb);
}