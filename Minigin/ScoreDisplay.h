#pragma once
#include "Component.h"
#include "QbertObserver.h"

namespace dae
{
	class TextComponent;

	class ScoreDisplay: public QbertObserver, public Component
	{
	public:
		ScoreDisplay(const std::shared_ptr<GameObject>& pGameObject);
		void Update() override;
		void Render() const override;
		void Died(EnemyThatDied enemyThatDied) override;
		void FellOff(EnemyThatDied enemyThatDied) override;
		void ChangeTile() override;

		virtual ~ScoreDisplay() = default;
		ScoreDisplay(const ScoreDisplay& other) = delete;
		ScoreDisplay(ScoreDisplay&& other) = delete;
		ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
		ScoreDisplay& operator=(ScoreDisplay&& other) = delete;

	private:
		std::shared_ptr<TextComponent> m_pText;
		int m_Score{};
	};
}
