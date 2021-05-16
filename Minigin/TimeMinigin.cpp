#include "MiniginPCH.h"
#include "TimeMinigin.h"



const float& dae::TimeMinigin::GetDeltaTime() const
{
	return m_DeltaTime;
}

void dae::TimeMinigin::SetDeltaTime(const float deltaTime)
{
	m_DeltaTime = deltaTime;
}
