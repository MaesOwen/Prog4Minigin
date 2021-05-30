#include "MiniginPCH.h"
#include "ChangeTile.h"


#include "AudioLocator.h"
#include "GameObject.h"
#include "Sprite.h"
#include "QbertComponent.h"

dae::ChangeTile::ChangeTile(const std::shared_ptr<GameObject>& pGameObject)
	:Command(pGameObject)
{
}

void dae::ChangeTile::execute()
{
	auto qbert = m_pGameObject->GetComponent<QbertComponent>();

	if (qbert)
	{
		qbert->ChangeTile();
		AudioLocator::GetInstance().GetAudioSystem()->Play(0, 0.05f);
	}
}
