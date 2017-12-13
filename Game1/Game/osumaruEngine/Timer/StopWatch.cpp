#include "engineStdafx.h"
#include "StopWatch.h"


StopWatch::StopWatch()
{
	m_time = 0.0;
	m_start = 0;
	m_end = 0;
	m_frequency = 1;
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
	QueryPerformanceCounter((LARGE_INTEGER*)&m_end);
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	m_time = (double)(m_end - m_start) / m_frequency;
}


