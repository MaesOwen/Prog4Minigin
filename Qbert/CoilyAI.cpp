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
			m_ElapsedSeconds -= m_TimeBetweenAIDecisions;
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
	if (isActive)
	{
		auto crossJump = m_pOwner->GetComponent<CrossJump>();
		if (crossJump)
		{
			m_pCrossJump = crossJump.get();
			m_IsActiveAI = isActive;
		}

	}
	else
	{
		m_IsActiveAI = isActive;
	}

}

void dae::CoilyAI::MoveTowardsTarget()
{
	auto targetCrossjump = m_pTarget->GetComponent<CrossJump>();
	if (targetCrossjump)
	{
		auto targetCoords = targetCrossjump->GetCurrentCoords();
		auto coords = m_pCrossJump->GetCurrentCoords();

		int row = targetCoords.row - coords.row;
		int col = targetCoords.col - coords.col;

		if (row == 0)
			row -= 1;
		if (col == 0)
			col += 1;

		row = row / abs(row);
		col = col / abs(col);

		std::cout << "jump row: " << row << ", col: " << col << std::endl;

		m_pCrossJump->JumpColRow(row, col);
	}


}
