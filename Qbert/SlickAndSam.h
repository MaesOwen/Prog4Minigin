#pragma once
#include "Component.h"

namespace dae
{
	class SlickAndSam: public dae::Component
	{
	public:
		SlickAndSam(int slickWidth, int slickHeight, bool isSlick);
		void Update() override;
		void Render() const override;
		void SetOwner(dae::GameObject* pOwner) override;
	
	private:
		bool m_IsSlick;
		int m_SlickAndSamWidth;
		int m_SlickAndSamHeight;

		void CheckForSpriteComponent();
	};
	
}
