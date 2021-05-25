#include "MiniginPCH.h"
#include "JumpBottomRight.h"

#include "CrossJump.h"
#include "GameObject.h"

dae::JumpBottomRight::JumpBottomRight(const std::shared_ptr<GameObject>& pGameObject)
	:Command(pGameObject)
{
}

void dae::JumpBottomRight::execute()
{
	if (m_pGameObject)
	{
		auto crossJump = m_pGameObject->GetComponent<CrossJump>();
		crossJump->Jump(CrossJump::DirCrossJump::bottomRight);
	}
}
