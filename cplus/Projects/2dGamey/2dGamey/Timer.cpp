#include "pch.h"
#include "Timer.h"

M_TMR::Timer::Timer() :
	m_elapsedTicks{0},
	m_totalTicks{0},
	m_leftOverTicks{0},
	m_frameCount{0},
	m_framesPerSecond{0},
	m_framesThisSecond{0},
	m_qpSecondCounter{0},
	m_fixedTimeStep{false},
	m_targetElapsedTicks{ TicksPerSecond / 60 }
{

	if (!QueryPerformanceFrequency(&m_qpFrequency))
	{
		throw std::exception();
	}

	if (!QueryPerformanceCounter(&m_qpCounter))
	{
		throw std::exception();
	}

	// Initialize max delta to 1/10 of a second.
	m_qpCounterMax = static_cast<uint64_t>(m_qpFrequency.QuadPart / 10);
}

uint32_t M_TMR::Timer::getFrameCount()
{
	return m_frameCount;
}

uint32_t M_TMR::Timer::getFramePerSecond()
{
	return m_framesPerSecond;
}

uint64_t M_TMR::Timer::getELapsedTicks()
{
	return m_elapsedTicks;
}

uint64_t M_TMR::Timer::getTotalTicks()
{
	return m_totalTicks;
}

double M_TMR::Timer::getElapsedSeconds()
{
	return TicksToSeconds(m_elapsedTicks);
}

double M_TMR::Timer::getTotalSeconds()
{
	return TicksToSeconds(m_totalTicks);
}
