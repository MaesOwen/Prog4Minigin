#pragma once
#include "Component.h"

namespace dae
{
	class Coily final: public dae::Component
	{
	public:
		Coily(int coilyWidth, int coilyHeight);
		void Render() const override;
		void Update() override;
		void SetOwner(GameObject* pOwner) override;

	private:
		int m_CoilyHeight;
		int m_CoilyWidth;

		void CheckForSpriteComponent();
		void CheckForAIComponents();
	};
	
}
