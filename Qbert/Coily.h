#pragma once
#include "Component.h"
#include "QbertSubject.h"

namespace dae
{
	class Coily final: public Component, public QbertSubject
	{
	public:
		Coily(int coilyWidth, int coilyHeight);
		void Render() const override;
		void Update() override;
		void Die() override;
		void FallOff() override;
		void ChangeTile() override;
		void SetOwner(GameObject* pOwner) override;

	private:
		int m_CoilyHeight;
		int m_CoilyWidth;

		void CheckForSpriteComponent();
		void CheckForAIComponents();
	};
	
}
