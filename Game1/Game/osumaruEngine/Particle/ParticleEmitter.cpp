#include "engineStdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "../Engine.h"

ParticleEmitter::ParticleEmitter() :
	m_pCamera(nullptr),
	m_info{},
	m_lifeTimer(0.0f),
	m_intervalTime(1.0f),
	m_particleNum(1)
{
}

ParticleEmitter::~ParticleEmitter()
{

}

void ParticleEmitter::Init(const SParticleEmittInfo& info, const Camera* camera)
{
	m_info = info;
	m_pCamera = camera;
	m_lifeTimer = info.emitterLifeTime;
	m_intervalTime = m_info.emittIntervalTime;
	if (info.isFirstTimeRandom)
	{
		m_intervalTime *= (float)GetRandom().GetRandDouble();
	}
	if (1 <= info.particleNum)
	{
		m_particleNum = info.particleNum;
	}

}

void ParticleEmitter::Update()
{
	m_intervalTime += GetGameTime().GetDeltaFrameTime();
	//一定時間たつとパーティクルを生成
	if (m_info.emittIntervalTime <= m_intervalTime)
	{
		m_intervalTime = 0.0f;
		for (int i = 0; i < m_particleNum; i++)
		{
			Particle* particle = New<Particle>(2);
			particle->Init(m_info, m_pCamera);
		}
	}
	//寿命が設定されている場合
	if (0.0f < m_lifeTimer)
	{
		m_lifeTimer -= GetGameTime().GetDeltaFrameTime();
		//寿命がなくなるとエミッターが死ぬ
		if (m_lifeTimer < 0.0f)
		{
			Delete(this);
		}
	}
}