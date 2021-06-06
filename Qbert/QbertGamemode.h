#pragma once
#include "Component.h"
#include "QbertObserver.h"

namespace dae
{
	class QbertGamemode: public Component, public QbertObserver
	{
	public:
		enum class Gamemode { Singleplayer, CoOp, Versus };

		QbertGamemode(Gamemode gamemode, GameObject* levelGridGameObject,
			GameObject* p1QbertGO, GameObject* p2QbertGO, GameObject* coilyGO,
			GameObject* slickGO, GameObject* samGO);
		void Update() override;
		void Render() const override;
		void Died(EnemyThatDied enemyThatDied) override;
		void ChangeTile() override;
		void FellOff(EnemyThatDied enemyThatDied) override;
	
	private:
		Gamemode m_CurrentGamemode;
		GameObject* m_LevelGrid;
		GameObject* m_P1QbertGO;
		GameObject* m_P2QbertGO;
		GameObject* m_CoilyGO;
		GameObject* m_SlickGO;
		GameObject* m_SamGO;
		//GameObject* m_ScoreGO;
		//vector levels

		void CheckWhoDiedFellOff(EnemyThatDied enemyThatDied);
		void SetUpGamemode(Gamemode gamemode);
		void SetUpSingleplayer();
		void SlickDied();
		void SamDied();
		void QbertDied();
		void CoilyDied();
		void CheckIfAllTilesAreDesiredColor();
	};
	
}
