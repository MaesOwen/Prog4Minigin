#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "TextComponent.h"
#include "Time.h"

dae::FPSComponent::FPSComponent(const std::shared_ptr<TextComponent>& pTextComponent)
	:m_pTextComponent(pTextComponent)
{
}

void dae::FPSComponent::Update()
{
	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->SetText(std::to_string(int(m_Second / Time::GetInstance().GetDeltaTime())) + " FPS");
		m_pTextComponent->Update();
	}
}

void dae::FPSComponent::Render() const
{
	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->Render();
	}
}

void dae::FPSComponent::SetPosition(float x, float y)
{
	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->SetPosition(x, y);
	}
}

