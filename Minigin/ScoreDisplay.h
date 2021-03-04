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
		void Died() override;
		void ChangeTile() override;

	private:
		std::shared_ptr<TextComponent> m_pText;
		int m_Score{};
	};
}
