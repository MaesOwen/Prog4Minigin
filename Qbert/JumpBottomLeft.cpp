#include "MiniginPCH.h"
#include "JumpBottomLeft.h"

#include "GameObject.h"
#include "CrossJump.h"

dae::JumpBottomLeft::JumpBottomLeft(const std::shared_ptr<GameObject>& gameObject)
	:Command(gameObject)
{
}

void dae::JumpBottomLeft::execute()
{
	if (m_pGameObject)
	{
		auto crossJump = m_pGameObject->GetComponent<CrossJump>();
		crossJump->Jump(CrossJump::DirCrossJump::bottomLeft);
	}
}
