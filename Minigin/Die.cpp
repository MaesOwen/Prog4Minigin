#include "MiniginPCH.h"
#include "Die.h"


#include "AudioLocator.h"
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
		AudioLocator::GetInstance().GetAudioSystem()->Play(0, 0.05f);
		qbert->Die();
	}
}
