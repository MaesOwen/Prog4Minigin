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

void dae::ScoreDisplay::Died(EnemyThatDied enemyThatDied)
{
	switch (enemyThatDied)
	{
	case EnemyThatDied::Coily:
		break;
	case EnemyThatDied::Slick:
		m_Score += 300;
		break;
	case EnemyThatDied::Sam:
		m_Score += 300;
		break;
	case EnemyThatDied::Qbert:
		break;
	}
	if (m_pText)
	{
		m_pText->SetText("Score: " + std::to_string(m_Score));
	}
}

void dae::ScoreDisplay::FellOff(EnemyThatDied enemyThatDied)
{
	switch (enemyThatDied)
	{
	case EnemyThatDied::Coily:
		m_Score += 500;
		break;
	case EnemyThatDied::Slick:
		break;
	case EnemyThatDied::Sam:
		break;
	case EnemyThatDied::Qbert:
		break;
	}
	if (m_pText)
	{
		m_pText->SetText("Score: " + std::to_string(m_Score));
	}
}

void dae::ScoreDisplay::ChangeTile()
{
	m_Score += 25;
	if (m_pText)
	{
		m_pText->SetText("Score: " + std::to_string(m_Score));
	}
}


