#include "MiniginPCH.h"
#include "QbertGamemode.h"

#include "GameObject.h"
#include "Platform.h"

dae::QbertGamemode::QbertGamemode(Gamemode gamemode, GameObject* levelGridGO, GameObject* p1QbertGO, GameObject* p2QbertGO, GameObject* coilyGO, GameObject* slickGO, GameObject* samGO)
	:m_CurrentGamemode(gamemode)
	, m_LevelGrid(levelGridGO)
	, m_P1QbertGO(p1QbertGO)
	, m_P2QbertGO(p2QbertGO)
	, m_CoilyGO(coilyGO)
	, m_SlickGO(slickGO)
	, m_SamGO(samGO)
{
	SetUpGamemode(gamemode);
}

void dae::QbertGamemode::Update()
{
}

void dae::QbertGamemode::Render() const
{
}

void dae::QbertGamemode::Died(EnemyThatDied enemyThatDied)
{
	CheckWhoDiedFellOff(enemyThatDied);
}

void dae::QbertGamemode::ChangeTile()
{
	CheckIfAllTilesAreDesiredColor();
}

void dae::QbertGamemode::FellOff(EnemyThatDied enemyThatDied)
{
	CheckWhoDiedFellOff(enemyThatDied);
}

void dae::QbertGamemode::CheckWhoDiedFellOff(EnemyThatDied enemyThatDied)
{
	switch (enemyThatDied)
	{
	case EnemyThatDied::Qbert:
		QbertDied();
		break;
	case EnemyThatDied::Coily:
		CoilyDied();
		break;
	case EnemyThatDied::Slick:
		SlickDied();
		break;
	case EnemyThatDied::Sam:
		SamDied();
		break;
	}
}

void dae::QbertGamemode::SetUpGamemode(Gamemode gamemode)
{
	switch (gamemode)
	{
	case Gamemode::Singleplayer:
		SetUpSingleplayer();
		break;
	case Gamemode::CoOp:
		break;
	case Gamemode::Versus:
		break;
	}
}

void dae::QbertGamemode::SetUpSingleplayer()
{
	if (m_P2QbertGO)
		m_P2QbertGO->SetIsActive(false);
}

void dae::QbertGamemode::SlickDied()
{
	std::cout << "Slick has died, remove from level." << std::endl;
	m_SlickGO->SetIsActive(false);
}

void dae::QbertGamemode::SamDied()
{
	std::cout << "Sam has died, remove from level." << std::endl;
	m_SamGO->SetIsActive(false);
}

void dae::QbertGamemode::QbertDied()
{
	std::cout << "Qbert has died, reset if 0 lives." << std::endl;
}

void dae::QbertGamemode::CoilyDied()
{
	std::cout << "Coily has died, remove from level." << std::endl;
	m_CoilyGO->SetIsActive(false);
}

void dae::QbertGamemode::CheckIfAllTilesAreDesiredColor()
{
	std::cout << "Tile has changed check if complete" << std::endl;
	int platformCount = 0;
	int completePlatformCount = 0;
	auto weakChildGOs = m_LevelGrid->GetChildren();
	for (auto weakChildGO : weakChildGOs)
	{
		if(auto sharedChildGO = weakChildGO.lock())
		{
			if (auto platform = sharedChildGO->GetComponent<Platform>())
			{
				if (!platform->IsSpinningDisk())
					platformCount++;
				if (platform->IsTargetColor())
					completePlatformCount++;
			}
		}
	}
	std::cout << m_LevelGrid->GetChildCount() << std::endl;
	std::cout << "platforms: " << platformCount << ", complete: " << completePlatformCount << std::endl;
}
