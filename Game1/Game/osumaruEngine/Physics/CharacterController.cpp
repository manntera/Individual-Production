#include "engineStdafx.h"
#include "CharacterController.h"
#include "Physics.h"
#include "CollisionAttr.h"
#include "../Engine.h"


//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;								//�Փ˃t���O�B
	D3DXVECTOR3 hitPos = { 0.0f, 0.0f, 0.0f };		//�Փ˓_�B
	D3DXVECTOR3 startPos = { 0.0f, 0.0f, 0.0f };	//���C�̎n�_�B
	D3DXVECTOR3 hitNormal = { 0.0f, 0.0f, 0.0f };	//�Փ˓_�̖@��
	const btCollisionObject* hitObject = nullptr;
	const btCollisionObject* me = nullptr;				//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
	float dist = FLT_MAX;							//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
													//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == me ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Detection)
		{
			//�����ɏՓ˂����Bor�L�����N�^�����̃R���W�����ƏՓ˂����B
			return 0.0f;
		}
		hitObject = convexResult.m_hitCollisionObject;
		//�Փ˓_�̖@�������������Ă���
		D3DXVECTOR3	hitNormalTmp = D3DXVECTOR3(convexResult.m_hitNormalLocal);
		//������Ɩ@���̂Ȃ��p�x�����߂�B
		D3DXVECTOR3 up = { 0.0f, 1.0f, 0.0f };
		float angle = D3DXVec3Dot(&hitNormalTmp, &up);
		angle = fabsf(acosf(angle));
		if (angle < cPI * 0.3f ||		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B�p�x�����W�A���P�ʂȂ̂�180�x��cPI
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground)//�������̓R���W�����������n�ʂƎw�肳��Ă���B
		{

			//�Փ˂��Ă���B
			isHit = true;
			D3DXVECTOR3 hitPosTmp = D3DXVECTOR3(convexResult.m_hitPointLocal);
			//�Փ˓_�̋��������߂�B
			D3DXVECTOR3 vDist;
			vDist = hitPosTmp - startPos;
			float distTmp = D3DXVec3Length(&vDist);
			if (dist > distTmp)
			{
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
				hitPos = hitPosTmp;
				hitNormal = D3DXVECTOR3(convexResult.m_hitNormalLocal);
				dist = distTmp;
			}
		}
		return 0.0f;
	}
};

//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�V��p)
struct SweepResultCeiling : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;								//�Փ˃t���O�B
	D3DXVECTOR3 hitPos = { 0.0f, 0.0f, 0.0f };		//�Փ˓_�B
	D3DXVECTOR3 startPos = { 0.0f, 0.0f, 0.0f };	//���C�̎n�_�B
	D3DXVECTOR3 hitNormal = { 0.0f, 0.0f, 0.0f };	//�Փ˓_�̖@��
	const btCollisionObject* hitObject = nullptr;
	const btCollisionObject* me = nullptr;				//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
	float dist = FLT_MAX;							//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
													//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == me ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Detection)
		{
			//�����ɏՓ˂����Bor�L�����N�^�����̃R���W�����ƏՓ˂����B
			return 0.0f;
		}
		hitObject = convexResult.m_hitCollisionObject;
		//�Փ˓_�̖@�������������Ă���
		D3DXVECTOR3	hitNormalTmp = D3DXVECTOR3(convexResult.m_hitNormalLocal);
		//�������Ɩ@���̂Ȃ��p�x�����߂�B
		D3DXVECTOR3 up = { 0.0f, -1.0f, 0.0f };
		float angle = D3DXVec3Dot(&hitNormalTmp, &up);
		angle = fabsf(acosf(angle));
		if (angle < cPI * 0.3f ||		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B�p�x�����W�A���P�ʂȂ̂�180�x��cPI
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground)//�������̓R���W�����������n�ʂƎw�肳��Ă���B
		{
			//�Փ˂��Ă���B
			isHit = true;
			D3DXVECTOR3 hitPosTmp = D3DXVECTOR3(convexResult.m_hitPointLocal);
			//�Փ˓_�̋��������߂�B
			D3DXVECTOR3 vDist;
			vDist = hitPosTmp - startPos;
			float distTmp = D3DXVec3Length(&vDist);
			if (dist > distTmp)
			{
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
				hitPos = hitPosTmp;
				hitNormal = D3DXVECTOR3(convexResult.m_hitNormalLocal);
				dist = distTmp;
			}
		}
		return 0.0f;
	}
};

//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;								//�Փ˃t���O�B
	D3DXVECTOR3 hitPos = { 0.0f, 0.0f, 0.0f };		//�Փ˓_�B
	D3DXVECTOR3 startPos = { 0.0f, 0.0f, 0.0f };	//���C�̎n�_�B
	D3DXVECTOR3 ray = { 0.0f, 0.0f, 0.0f };
	bool		isRay = false;
	float		distance = 0.0f;
	float dist = FLT_MAX;							//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
	D3DXVECTOR3	hitNormal = { 0.0f, 0.0f, 0.0f };	//�Փ˓_�̖@��
	const btCollisionObject* me = NULL;					//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
	const btCollisionObject* hitObject = NULL;
													//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐�
	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == me ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Detection)
		{
			//�����ɏՓ˂����Bor�n�ʂɏՓ˂����B
			return 0.0f;
		}
		hitObject = convexResult.m_hitCollisionObject;
		//�Փ˓_�̖@�������������Ă���B
		D3DXVECTOR3 hitNormalTmp;
		hitNormalTmp = D3DXVECTOR3(convexResult.m_hitNormalLocal);
		//������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�
		D3DXVECTOR3 up = { 0.0f, 1.0f, 0.0f };
		float angle = D3DXVec3Dot(&hitNormalTmp, &up);
		angle = fabsf(acosf(angle));
		if (angle >= cPI * 0.3f ||		//�n�ʂ̌X�΂�54�x�ȏ�Ȃ̂ŕǂƂ݂Ȃ��B
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character)//�������̓R���W�����������L�����N�^�Ȃ̂ŕǂƂ݂Ȃ��B
		{
			D3DXVec3Normalize(&ray, &ray);
			btVector3 btMoveSpeed = hitObject->getWorldTransform().getOrigin() - hitObject->getOneBeforeWorldTransform().getOrigin();
			D3DXVECTOR3 moveSpeed = { btMoveSpeed.x(), btMoveSpeed.y(), btMoveSpeed.z() };
			distance = D3DXVec3Length(&moveSpeed);
			if (FLT_EPSILON <= distance)
			{
				D3DXVec3Normalize(&moveSpeed, &moveSpeed);
				if (D3DXVec3Dot(&ray, &moveSpeed) < 0.0f)
				{
					isRay = true;
				}
			}
			isHit = true;
			D3DXVECTOR3 hitPosTmp;
			hitPosTmp = D3DXVECTOR3(convexResult.m_hitPointLocal);
			//��_�Ƃ̋����𒲂ׂ�B
			D3DXVECTOR3 vDist;
			vDist = hitPosTmp - startPos;
			vDist.y = 0.0f;
			float distTmp = D3DXVec3Length(&vDist);
			if (distTmp < dist)
			{
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
				hitPos = hitPosTmp;
				dist = distTmp;
				hitNormal = hitNormalTmp;
			}
		}
		return 0.0f;
	}
};

CharacterController::CharacterController() :
	m_position(0.0f, 0.0f, 0.0f),
	m_moveSpeed(0.0f, 0.0f, 0.0f),
	m_isJump(false),
	m_isOnGround(true),
	m_collider(),
	m_radius(0.0f),
	m_height(0.0f),
	m_rigidBody(),
	m_gravity(-9.8f),
	m_groundHitObject(nullptr),
	m_wallHitObject(nullptr),
	m_wallNormal(0.0f, 0.0f, 0.0f)
{
}

CharacterController::~CharacterController()
{
	RemovedRigidBody();
}

void CharacterController::Init(float radius, float height, const D3DXVECTOR3& position)
{
	m_position = position;
	m_moveSpeed = {0.0f, 0.0f, 0.0f};
	//�R���W�����쐬�B
	m_radius = radius;
	m_height = height;
	m_collider.Create(m_radius, m_height);

	//���̂��������B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	//���̂̈ʒu���X�V�B
	m_rigidBody.SetPosition(m_position);
	//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.SetUserIndex(enCollisionAttr_Character);
	m_rigidBody.SetCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
}

void CharacterController::Execute(float deltaTime)
{

	StaticExecute();
	PhysicsWorld& physicsWorld = GetPhysicsWorld();
	//���x�ɏd�͉����x��������B
	m_moveSpeed.y += m_gravity * deltaTime;
	//���̈ړ���ƂȂ���W���v�Z����B
	D3DXVECTOR3 nextPosition = m_position;
	//���x���炱�̃t���[���ł̈ړ��ʂ����߂�B�I�C���[�ϕ��B
	D3DXVECTOR3 addPos = m_moveSpeed;
	addPos *= deltaTime;
	nextPosition += addPos;
	D3DXVECTOR3 originalXZDir = addPos;
	originalXZDir.y = 0.0f;
	D3DXVec3Normalize(&originalXZDir, &originalXZDir);

	//XZ���ʂł̏Փˌ��o�ƏՓˉ������s���B
	{
		int loopCount = 0;
		const btCollisionObject* wallCollisionObject = nullptr;
		D3DXVECTOR3 hitNormal = { 0.0f, 0.0f, 0.0f };
		while (true)
		{
			//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
			D3DXVECTOR3  addPosXZ;
			addPosXZ = nextPosition - m_position;
			addPosXZ.y = 0.0f;
			if (D3DXVec3Length(&addPosXZ) < FLT_EPSILON)
			{
				//XZ���ʂœ������Ȃ��̂Œ��ׂ�K�v�Ȃ��B
				//FLTEPSILON��1���傫���A�ŏ��̒l�Ƃ̍�����\���萔�B
				//�ƂĂ��������l�̂��Ƃł��B
				break;
			}
			//�J�v�Z���R���C�_�[�̒��S���W�@+ 0.2�̍��W��posTmp�ɋ��߂�B
			D3DXVECTOR3 posTmp = m_position;
			posTmp.y += m_height * 0.5f + m_radius + 0.2f;
			//���C���쐬�B
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmpd�ɋ��߂�B
			start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
			//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
			end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

			SweepResultWall callback;
			callback.me = m_rigidBody.GetBody();
			callback.startPos = posTmp;
			//�Փˌ��o�B
			physicsWorld.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
			if (callback.isHit)
			{
				wallCollisionObject = callback.hitObject;
				//���������B
				//�ǁB
				D3DXVECTOR3 vT0, vT1;
				//XZ���ʂł̈ړ���̍��W��vT0�ɁA��_(�Փ˓_)��vT1�ɐݒ肷��B
				vT0 = { nextPosition.x, 0.0f, nextPosition.z };
				vT1 = { callback.hitPos.x, 0.0f, callback.hitPos.z };
				//�߂荞�݂��������Ă���ړ��x�N�g�������߂�B
				D3DXVECTOR3 vMerikomi;
				vMerikomi = vT1 - vT0;

				//XZ���ʂł̏Փ˂����ǂ̖@�������߂�B
				D3DXVECTOR3 hitNormalXZ = callback.hitNormal;
				hitNormalXZ.y = 0.0f;
				D3DXVec3Normalize(&hitNormalXZ, &hitNormalXZ);
				hitNormal = hitNormalXZ;
				//�߂荞�݃x�N�g����ǂ̖@���Ɏˉe����B
				float fT0 = D3DXVec3Dot(&hitNormalXZ, &vMerikomi);
				//�����߂��Ԃ��x�N�g�������߂�B
				//�����Ԃ��x�N�g���͕ǂ̖@���Ɏˉe���ꂽ�߂荞�݃x�N�g���B
				D3DXVECTOR3 vOffset;
				vOffset = hitNormalXZ;
				vOffset *= (fT0 + m_radius);//�R���C�_�[�̔��a���蓮�Ŗ߂��Ă���
				nextPosition += vOffset;
				D3DXVECTOR3 currentDir;
				currentDir = nextPosition - m_position;
				currentDir.y = 0.0f;
				D3DXVec3Normalize(&currentDir, &currentDir);
				if (D3DXVec3Dot(&currentDir, &originalXZDir) < 0.0f)
				{
					//�p�ɓ��������̃L�����N�^�̐U����h�~���邽�߂ɁA
					//�ړ��悪�t����
					nextPosition.x = m_position.x;
					nextPosition.z = m_position.z;
					break;
				}
			}
			else
			{
				//�ǂ��Ƃ�������Ȃ��̂ŏI���B
				break;
			}
			m_wallHitObject = callback.hitObject;
			loopCount++;
			if (loopCount == 5)
			{
				break;
			}
			if (callback.hitObject != nullptr && m_rigidBody.GetBody()->getUserIndex() == enCollisionAttr_Character)
			{
				const_cast<btCollisionObject*>(callback.hitObject)->setPlayerCollisionWallFlg(true);
			}
		}
		m_wallNormal = hitNormal;
		m_wallHitObject = wallCollisionObject;
	}
	//XZ�̈ړ��͊m��B
	m_position.x = nextPosition.x;
	m_position.z = nextPosition.z;

	D3DXVECTOR3 addPosY;
	addPosY = nextPosition - m_position;
	//�������𒲂ׂ�B
	{
		m_position = nextPosition;	//�ړ��̉��m��B
									//���C���쐬����B
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
		start.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
		//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
		//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������B
		//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
		D3DXVECTOR3 endPos;
		endPos = D3DXVECTOR3(start.getOrigin());
		if (!m_isOnGround)
		{
			if (addPosY.y > 0.0f)
			{
				//�W�����v���Ƃ��ŏ㏸���B
				//�㏸���ł�XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŉ��𒲂ׂ�B
				endPos.y -= addPosY.y * 0.01f;
			}
			else
			{
				endPos.y += addPosY.y;
			}
		}
		else
		{
			//�n�ʏ�ɂ���ꍇ��1m��������B
			endPos.y -= 1.0f;
		}
		end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
		SweepResultGround callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos = D3DXVECTOR3(start.getOrigin());
		//�Փˌ��o�B
		if (fabsf(addPosY.y) > FLT_EPSILON && (start.getOrigin().y() - end.getOrigin().y() != 0.0f))
		{
			physicsWorld.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
		}
		if (callback.isHit)
		{
			//���������B
			m_moveSpeed.y = 0.0f;
			m_isJump = false;
			m_isOnGround = true;
			nextPosition.y = callback.hitPos.y;
		}
		else
		{
			//�n�ʏ�ɂ��Ȃ�
			m_isOnGround = false;
		}
		if (callback.hitObject != nullptr && m_rigidBody.GetBody()->getUserIndex() == enCollisionAttr_Character)
		{
			//const_cast<btCollisionObject*>(callback.hitObject)->setPlayerCollisionGroundFlg(true);
		}
		m_groundHitObject = callback.hitObject;

	}//������𒲂ׂ�
	{
		m_position = nextPosition;	//�ړ��̉��m��B
									//���C���쐬����B
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
		start.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
		//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
		//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������B
		//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
		D3DXVECTOR3 endPos;
		endPos = D3DXVECTOR3(start.getOrigin());
		if (!m_isOnGround)
		{
			if (addPosY.y > 0.0f)
			{
				//�W�����v���Ƃ��ŏ㏸���B
				//�㏸���ł�XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŉ��𒲂ׂ�B
				endPos.y += addPosY.y;
			}
			else
			{
				endPos.y -= addPosY.y * 0.01f;
			}
		}
		end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
		SweepResultCeiling callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos = D3DXVECTOR3(start.getOrigin());
		//�Փˌ��o�B
		if (fabsf(addPosY.y) > FLT_EPSILON && (start.getOrigin().y() - end.getOrigin().y() != 0.0f))
		{
			physicsWorld.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
		}
		if (callback.isHit)
		{
			//���������B
			m_moveSpeed.y = 0.0f;
			nextPosition.y = callback.hitPos.y - (m_height + m_radius * 2.0f + 0.1f);
		}
	}
	//�ړ��m��B
	m_position = nextPosition;
	const btRigidBody* btBody = m_rigidBody.GetBody();
	//���̂𓮂����B
	btBody->setActivationState(DISABLE_DEACTIVATION);
	//���̂̈���X�V
	m_rigidBody.SetPosition(m_position);
	//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
}

void CharacterController::StaticExecute()
{
	const int rayNum = 4;
	const float rayLength = 5.0f;
	D3DXVECTOR3 ray[rayNum] =
	{
		{ rayLength,	0.0f, 0.0f},
		{ -rayLength,	0.0f, 0.0f },
		{ 0.0f,			0.0f, rayLength },
		{ 0.0f,			0.0f, -rayLength },
	};

	for (int i = 0; i < rayNum; i++)
	{
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		D3DXVECTOR3 endPos = m_position;
		end.setOrigin(btVector3(endPos.x, endPos.y + m_height * 0.5f + m_radius , endPos.z));
		D3DXVECTOR3 startPos = m_position;
		startPos += ray[i];
		start.setOrigin(btVector3(startPos.x, end.getOrigin().y(), startPos.z));
		SweepResultWall callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos = startPos;
		callback.ray = D3DXVECTOR3(end.getOrigin() - start.getOrigin());
		GetPhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
		if(callback.isHit && callback.isRay/* && rayLength - callback.dist < m_radius - 0.001f*/)
		{
			D3DXVECTOR3 hitNormal = callback.hitNormal;
			hitNormal.y = 0.0f;
			D3DXVec3Normalize(&hitNormal, &hitNormal);
			m_wallNormal = hitNormal;
			D3DXVECTOR3 sinking;
			sinking = callback.hitPos - D3DXVECTOR3(end.getOrigin());
			sinking.y = 0.0f;
			float projection = D3DXVec3Dot(&hitNormal, &sinking);
			hitNormal *= (projection + m_radius);
			m_position += hitNormal;
		}
	}
	//���̂̈ʒu���X�V
	//m_rigidBody.SetPosition(m_position);
}

void CharacterController::RemovedRigidBody()
{
	m_rigidBody.Release();
}

void CharacterController::Draw()
{
	btTransform transform = m_rigidBody.GetBody()->getWorldTransform();

	btVector3& position = transform.getOrigin();
	//position.setY(position.y() + m_radius + m_height * 0.5f);
	GetPhysicsWorld().DebugDraw(transform, const_cast<btCollisionShape*>(m_collider.GetBody()));
}