#pragma once
#include "Component.h"
#include "QbertSubject.h"

namespace dae
{
	class SlickAndSam: public Component, public QbertSubject
	{
	public:
		SlickAndSam(int slickWidth, int slickHeight, bool isSlick);
		void Update() override;
		void Render() const override;
		void SetOwner(dae::GameObject* pOwner) override;
		void Die() override;
		void FallOff() override;
		void ChangeTile() override;
	
	private:
		bool m_IsSlick;
		int m_SlickAndSamWidth;
		int m_SlickAndSamHeight;

		void CheckForSpriteComponent();
	};
	
}
