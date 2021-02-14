#pragma once
#include <memory>

namespace dae
{
	
	class TextComponent;
	class FPSComponent
	{
	public:
		FPSComponent(const std::shared_ptr<TextComponent>& pTextComponent);
		void Update();
		void Render() const;
		void SetPosition(float x, float y);
	private:
		std::shared_ptr<TextComponent> m_pTextComponent;
		const double m_Second = 1.0;
	};

}
