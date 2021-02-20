#pragma once
#include <memory>

#include "Component.h"

namespace dae
{
	
	class TextComponent;
	class FPSComponent final: public Component
	{
	public:
		
		void Update() override;
		void Render() const override;
		void SetOwner(std::shared_ptr<GameObject> pOwner) override;
		void SetPosition(float x, float y);

		FPSComponent() = default;
	private:
		std::shared_ptr<TextComponent> m_pTextComponent;
		const double m_Second = 1.0;
		float m_AverageDeltaTime = 0.f;
		float m_ElapsedTime = 0.f;
		float m_FPSIntervalSeconds = 3.f;
	};

}
