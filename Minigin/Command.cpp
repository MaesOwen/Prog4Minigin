#include "MiniginPCH.h"
#include "Command.h"

dae::Command::Command(const std::shared_ptr<GameObject>& pGameObject)
	:m_pGameObject(pGameObject)
{
}
