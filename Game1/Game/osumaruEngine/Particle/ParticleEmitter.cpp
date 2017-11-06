#include "engineStdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "../Engine.h"

ParticleEmitter::ParticleEmitter()
{
	m_intervalTime = 0.0f;
	m_lifeTimer = 0.0f;
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

}

void ParticleEmitter::Update()
{
	m_intervalTime += 1.0f / 60.0f;
	if (m_info.emittIntervalTime <= m_intervalTime)
	{
		m_intervalTime = 0.0f;
		Particle* particle = New<Particle>(0);
		particle->Init(m_info, m_camera);
	}
	if (0.0f < m_lifeTimer)
	{
		m_lifeTimer -= 1.0f / 60.0f;
		if (m_lifeTimer < 0.0f)
		{
			Delete(this);
		}
	}
}