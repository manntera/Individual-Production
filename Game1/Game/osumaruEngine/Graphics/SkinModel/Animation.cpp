#include "engineStdafx.h"
#include "Animation.h"

Animation::Animation()
{
	m_pAnimController = nullptr;
	m_numAnimSet = 0;
	m_isBlending = false;
	m_isInterpolate = false;
	m_numMaxTracks = 0;
	m_interpolateEndTime = 0.0f;
	m_interpolateTime = 0.0f;
}

Animation::~Animation()
{

}

void Animation::Init(ID3DXAnimationController* anim)
{
	m_pAnimController = anim;
	ID3DXAnimationSet* animSet;
	m_pAnimController->GetAnimationSet(0, &animSet);
	m_numAnimSet = m_pAnimController->GetMaxNumAnimationSets();
	m_numMaxTracks = m_pAnimController->GetMaxNumTracks();
	m_blendRateTable.reset(new float[m_numMaxTracks]);
	m_animationEndTime.reset(new double[m_numAnimSet]);
	m_animationSets.reset(new ID3DXAnimationSet*[m_numAnimSet]);
	for (int i = 0; i < m_numMaxTracks; i++)
	{
		m_blendRateTable[i] = 1.0f;
	}
	//アニメーションセットを初期化。
	for (int i = 0; i < m_numAnimSet; i++)
	{
		m_pAnimController->GetAnimationSet(i, &m_animationSets[i]);
		m_animationEndTime[i] = 0.0f;
	}
	m_localAnimationTime = 0.0f;
}

void Animation::PlayAnimation(int animationSetIndex)
{
	if (animationSetIndex < m_numAnimSet)
	{
		if (m_pAnimController)
		{
			m_currentAnimationSetNo = animationSetIndex;
			m_currentTrackNo = 0;
			//0番目以外のトラックは無効にする
			for (int i = 1; i < m_numMaxTracks; i++)
			{
				m_pAnimController->SetTrackEnable(i, FALSE);
			}
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackAnimationSet(m_currentTrackNo, m_animationSets[m_currentAnimationSetNo]);
			m_pAnimController->SetTrackEnable(0, TRUE);
			m_pAnimController->SetTrackPosition(0, 0.0f);
			m_localAnimationTime = 0.0;
		}
	}
	else
	{
		//アニメーションのインデックスが不正です
		std::abort();
	}
}

void Animation::PlayAnimation(int animationSetIndex, float interpolateTime)
{
	if (animationSetIndex < m_numAnimSet)
	{
		if (m_pAnimController)
		{
			//補間開始の印
			m_isInterpolate = true;
			this->m_interpolateTime = 0.0f;
			m_interpolateEndTime = interpolateTime;
			m_currentTrackNo = (m_currentTrackNo + 1) % m_numMaxTracks;
			m_pAnimController->SetTrackAnimationSet(m_currentTrackNo, m_animationSets[animationSetIndex]);
			m_pAnimController->SetTrackEnable(m_currentTrackNo, TRUE);
			m_pAnimController->SetTrackSpeed(m_currentTrackNo, 0.0f);
			m_localAnimationTime = 0.0;
			m_currentAnimationSetNo = animationSetIndex;
		}
	}
	else
	{
		//アニメーションのインデックスが不正です
		std::abort();
	}
}

void Animation::Update(float deltaTime)
{
	if (m_pAnimController)
	{
		m_localAnimationTime += deltaTime;
		if (m_animationEndTime[m_currentAnimationSetNo] > 0.0//アニメーションの終了時間が設定されている
			&& m_localAnimationTime > m_animationEndTime[m_currentAnimationSetNo])//アニメーションの終了時間を超えた
		{
			m_localAnimationTime -= m_animationEndTime[m_currentAnimationSetNo];
			m_pAnimController->SetTrackPosition(m_currentTrackNo, m_localAnimationTime);
			m_pAnimController->AdvanceTime(0, NULL);
		}
		else
		{
			//普通に再生
			m_pAnimController->AdvanceTime(deltaTime, NULL);
		}
		if (m_isInterpolate)
		{
			ID3DXAnimationSet* animSet = m_animationSets[2];
			float period = (float)animSet->GetPeriod();
			//補間中
			m_interpolateTime += deltaTime;
			float weight = 0.0f;
			if (m_interpolateEndTime < m_interpolateTime)
			{
				m_isInterpolate = false;
				weight = 1.0f;
				for (int i = 0; i < m_numMaxTracks; i++)
				{
					if (i != m_currentTrackNo)
					{
						m_pAnimController->SetTrackEnable(i, FALSE);
					}
				}
			}
			else
			{
				weight = m_interpolateTime / m_interpolateEndTime;
				float invWeight = 1.0f - weight;
				//ウェイトを設定していく
				for (int i = 0; i < m_numMaxTracks; i++)
				{
					if (i != m_currentTrackNo)
					{
						m_pAnimController->SetTrackWeight(i, m_blendRateTable[i] * invWeight);
					}
					else
					{
						m_pAnimController->SetTrackWeight(i, weight);
					}
				}
			}
		}
	}
}