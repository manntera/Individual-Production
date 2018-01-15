#include "engineStdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "../Engine.h"

ParticleEmitter::ParticleEmitter()
{
	m_intervalTime = 0.0f;
	m_lifeTimer = 0.0f;
	m_particleNum = 1;
}

ParticleEmitter::~ParticleEmitter()
{

}

void ParticleEmitter::Init(SParticleEmittInfo info, Camera* camera)
{
	m_info = info;
	m_camera = camera;
	m_lifeTimer = info.emitterLifeTime;
	m_intervalTime = m_info.emittIntervalTime;
	if (1 <= info.particleNum)
	{
		m_particleNum = info.particleNum;
	}

}

void ParticleEmitter::Update()
{
	m_intervalTime += GetGameTime().GetDeltaFrameTime();
	//��莞�Ԃ��ƃp�[�e�B�N���𐶐�
	if (m_info.emittIntervalTime <= m_intervalTime)
	{
		m_intervalTime = 0.0f;
		for (int i = 0; i < m_particleNum; i++)
		{
			Particle* particle = New<Particle>(2);
			particle->Init(m_info, m_camera);
		}
	}
	//�������ݒ肳��Ă���ꍇ
	if (0.0f < m_lifeTimer)
	{
		m_lifeTimer -= GetGameTime().GetDeltaFrameTime();
		//�������Ȃ��Ȃ�ƃG�~�b�^�[������
		if (m_lifeTimer < 0.0f)
		{
			Delete(this);
		}
	}
}