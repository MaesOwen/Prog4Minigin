#include "MiniginPCH.h"
#include "Die.h"

#include "GameObject.h"
#include "Qbert.h"

dae::Die::Die(const std::shared_ptr<GameObject>& pGameObject)
	:Command(pGameObject)
{
	
}

void dae::Die::execute()
{
	std::shared_ptr<Qbert> qbert = m_pGameObject->GetComponent<Qbert>();
	if (qbert)
	{
		qbert->Die();
	}
}
