#include "MiniginPCH.h"
#include "JumpTopLeft.h"

#include "CrossJump.h"
#include "GameObject.h"

dae::JumpTopLeft::JumpTopLeft(const std::shared_ptr<dae::GameObject>& gameObject)
	:Command(gameObject)
{
}

void dae::JumpTopLeft::execute()
{
	if (m_pGameObject)
	{
		auto crossJump = m_pGameObject->GetComponent<CrossJump>();
		crossJump->Jump(CrossJump::DirCrossJump::topLeft);
	}
}
