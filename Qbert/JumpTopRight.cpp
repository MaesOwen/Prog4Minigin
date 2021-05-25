#include "MiniginPCH.h"
#include "JumpTopRight.h"


#include "CrossJump.h"
#include "GameObject.h"

dae::JumpTopRight::JumpTopRight(const std::shared_ptr<GameObject>& pGameObject)
	:Command(pGameObject)
{
}

void dae::JumpTopRight::execute()
{
	if(m_pGameObject)
	{
		auto crossJump = m_pGameObject->GetComponent<CrossJump>();
		crossJump->Jump(CrossJump::DirCrossJump::topRight);
	}
}
