#include "engineStdafx.h"
#include "StopWatch.h"


StopWatch::StopWatch() :
	m_start(0),
	m_end(0),
	m_frequency(1),
	m_time(0.0f),
	m_millTime(0.0f)
{
}

StopWatch::~StopWatch()
{

}

void StopWatch::Start()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_start);
}

void StopWatch::Stop()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_end);
	m_time = (double)(m_end - m_start) / m_frequency;
	m_millTime = m_time * 1000.0;
}


