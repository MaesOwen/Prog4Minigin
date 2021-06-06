#pragma once
#include "Component.h"
#include "QbertObserver.h"
#include <memory>

#include "QbertComponent.h"

namespace dae
{
	class TextComponent;

	class LivesDisplay: public Component , public QbertObserver
	{
	public:
		LivesDisplay(const std::shared_ptr<GameObject>& pGameObject);
		void Update() override;
		void Render() const override;
		void Died(EnemyThatDied enemyThatDied) override;
		void FellOff(EnemyThatDied enemyThatDied) override;
		void ChangeTile() override;
		void SetQbert(const std::shared_ptr<QbertComponent> pQbert);
		void SetQbert(const std::weak_ptr<QbertComponent> pQbert);
		void SetQbert(QbertComponent* pQbert);

		virtual ~LivesDisplay();
		LivesDisplay(const LivesDisplay& other) = delete;
		LivesDisplay(LivesDisplay&& other) = delete;
		LivesDisplay& operator=(const LivesDisplay& other) = delete;
		LivesDisplay& operator=(LivesDisplay&& other) = delete;


	private:
		std::shared_ptr<TextComponent> m_pText;
		std::weak_ptr<QbertComponent> m_pPlayer;
	};
	
}
