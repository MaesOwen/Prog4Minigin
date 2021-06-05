#include "MiniginPCH.h"
#include "BallAI.h"


#include "CoilyAI.h"
#include "GameObject.h"
#include "QbertSprite.h"
#include "TimeMinigin.h"

dae::BallAI::BallAI()
	:m_IsActive(false)
	,m_TimeBetweenAIDecisions(1)
	,m_ElapsedSeconds(0)
{
	srand(unsigned(time(NULL)));
}

void dae::BallAI::Update()
{
	if(m_IsActive)
	{
		m_ElapsedSeconds += TimeMinigin::GetInstance().GetDeltaTime();
		
		if (m_pCrossJump && m_ElapsedSeconds >= m_TimeBetweenAIDecisions)
		{
			if (m_pCrossJump->IsOnBottomPlatform())
			{
				BottomReached();
			}else
			{
				JumpRandomDirectionDownwards();
			}
			
			
		}
	}
}

void dae::BallAI::Render() const
{
}

void dae::BallAI::SetOwner(dae::GameObject* pOwner)
{
	m_pOwner = pOwner;
	
	m_pCrossJump = m_pOwner->GetComponent<CrossJump>().get();
}

void dae::BallAI::StartAI()
{
	if(m_pCrossJump)
	{
		m_IsActive = true;
	}else
	{
		m_pCrossJump = m_pOwner->GetComponent<CrossJump>().get();
		if (m_pCrossJump)
			m_IsActive = true;
	}
		
	
}


void dae::BallAI::JumpRandomDirectionDownwards()
{
	m_ElapsedSeconds -= m_TimeBetweenAIDecisions;
	int side = rand() % 2;
	if (side > 0)
	{
		m_pCrossJump->Jump(CrossJump::DirCrossJump::bottomLeft);
	}
	else
	{
		m_pCrossJump->Jump(CrossJump::DirCrossJump::bottomRight);
	}
}

void dae::BallAI::BottomReached()
{
	auto coilySprite = m_pOwner->GetComponent<QbertSprite>();
	auto coilyAI = m_pOwner->GetComponent<CoilyAI>();
	
	if (coilySprite && coilyAI)
	{
		m_IsActive = false;
		coilySprite->SetIsBall(false);
		coilyAI->SetActiveAI(true);
	}
		

}
