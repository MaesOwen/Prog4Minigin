#include "MiniginPCH.h"
#include "LivesDisplay.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"

dae::LivesDisplay::LivesDisplay(const std::shared_ptr<GameObject>& pGameObject)
{
	std::shared_ptr<TextComponent> tc = pGameObject->GetComponent<TextComponent>();
	if (!tc)
	{
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		tc = std::make_shared<TextComponent>("Lives: ", font);
	}
	m_pText = tc;
}

void dae::LivesDisplay::Update()
{
}

void dae::LivesDisplay::Render() const
{
}

void dae::LivesDisplay::Died()
{
	if (m_pPlayer)
	{
		int lives = m_pPlayer->GetLives();
		m_pText->SetText("Lives: " + std::to_string(lives));
	}
	
}

void dae::LivesDisplay::ChangeTile()
{
}

void dae::LivesDisplay::SetQbert(const std::shared_ptr<Qbert>& pQbert)
{
	//m_pPlayer = std::make_shared<Qbert>(*pQbert);
	m_pPlayer = pQbert;
}

void dae::LivesDisplay::SetQbert(Qbert* pQbert)
{
	m_pPlayer = std::make_shared<Qbert>(*pQbert);
}
