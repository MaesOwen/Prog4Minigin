#include "MiniginPCH.h"
#include "Time.h"



const float& dae::Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

void dae::Time::SetDeltaTime(const float deltaTime)
{
	m_DeltaTime = deltaTime;
}
