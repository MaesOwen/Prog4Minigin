#include "MiniginPCH.h"
#include "CoilyAI.h"



#include "CrossJump.h"
#include "GameObject.h"
#include "TimeMinigin.h"
#include "TransformComponent.h"


dae::CoilyAI::CoilyAI()
	:m_ElapsedSeconds(0)
	, m_TimeBetweenAIDecisions(1)
	, m_IsActiveAI(false)
	, m_pTarget(nullptr)
{
}

void dae::CoilyAI::Update()
{
	if (m_IsActiveAI && m_pTarget && m_pCrossJump)
	{
		m_ElapsedSeconds += TimeMinigin::GetInstance().GetDeltaTime();

		if (m_ElapsedSeconds >= m_TimeBetweenAIDecisions)
		{
			MoveTowardsTarget();
		}
	}
}

void dae::CoilyAI::Render() const
{
}

void dae::CoilyAI::SetTarget(GameObject* target)
{
	m_pTarget = target;
}

void dae::CoilyAI::SetActiveAI(bool isActive)
{
	if(isActive)
	{
		auto crossJump = m_pOwner->GetComponent<CrossJump>();
		if (crossJump)
		{
			m_pCrossJump = crossJump.get();
			m_IsActiveAI = isActive;
		}
			
	}else
	{
		m_IsActiveAI = isActive;
	}
	
}

void dae::CoilyAI::MoveTowardsTarget()
{
	auto pos = m_pOwner->GetTransformComponent()->GetPosition();
	auto targetPos = m_pTarget->GetTransformComponent()->GetPosition();

	auto dir = targetPos - pos;

	if(dir.x > 0)
	{
		if(dir.y > 0)
		{
			m_pCrossJump->Jump(CrossJump::DirCrossJump::bottomRight);
		}else
		{
			m_pCrossJump->Jump(CrossJump::DirCrossJump::topRight);
		}
	}else
	{
		if (dir.y > 0)
		{
			m_pCrossJump->Jump(CrossJump::DirCrossJump::bottomLeft);
		}
		else
		{
			m_pCrossJump->Jump(CrossJump::DirCrossJump::topLeft);
		}
	}

	
}
