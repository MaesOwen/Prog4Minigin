#pragma once
#include "Component.h"
#include "QbertObserver.h"
#include <memory>

#include "Qbert.h"

namespace dae
{
	class TextComponent;

	class LivesDisplay: public Component , public QbertObserver
	{
	public:
		LivesDisplay(const std::shared_ptr<GameObject>& pGameObject);
		void Update() override;
		void Render() const override;
		void Died() override;
		void ChangeTile() override;
		void SetQbert(const std::shared_ptr<Qbert>& pQbert);
		void SetQbert(Qbert* pQbert);

	private:
		std::shared_ptr<TextComponent> m_pText;
		std::shared_ptr<Qbert> m_pPlayer;
	};
	
}
