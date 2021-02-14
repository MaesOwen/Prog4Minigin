#include "MiniginPCH.h"
#include "Time.h"


void dae::Time::Start()
{
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_PreviousTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<double>(m_CurrentTime - m_PreviousTime).count();
}

void dae::Time::Reset()
{
	m_PreviousTime = m_CurrentTime;
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<double>(m_CurrentTime - m_PreviousTime).count();
}

const double& dae::Time::GetDeltaTime() const
{
	return m_DeltaTime;
}
