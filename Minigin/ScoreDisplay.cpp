#include "MiniginPCH.h"
#include "ScoreDisplay.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "ResourceManager.h"

dae::ScoreDisplay::ScoreDisplay(const std::shared_ptr<GameObject>& pGameObject)
{
	std::shared_ptr<TextComponent> tc = pGameObject->GetComponent<TextComponent>();
	if (!tc)
	{
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		tc = std::make_shared<TextComponent>("Score: ", font);
	}
	m_pText = tc;
}

void dae::ScoreDisplay::Update()
{
}

void dae::ScoreDisplay::Render() const
{
}

void dae::ScoreDisplay::Died()
{
}

void dae::ScoreDisplay::ChangeTile()
{
	m_Score += 25;
	if(m_pText)
	{
		m_pText->SetText("Score: " + std::to_string(m_Score));
	}
}
