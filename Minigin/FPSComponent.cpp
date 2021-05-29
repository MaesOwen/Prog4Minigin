#include "MiniginPCH.h"
#include "FPSComponent.h"


#include "GameObject.h"
#include "TextComponent.h"
#include "TimeMinigin.h"

void dae::FPSComponent::Update()
{
	const float deltaTime = TimeMinigin::GetInstance().GetDeltaTime();
	m_ElapsedTime += deltaTime;
	m_AverageDeltaTime += deltaTime;
	m_AverageDeltaTime /= 2.f;
	
	if (m_ElapsedTime > m_FPSIntervalSeconds)
	{
		if (m_pTextComponent != nullptr)
		{
			m_pTextComponent->SetText(std::to_string(int(m_Second / m_AverageDeltaTime)) + " FPS");
		}
		m_AverageDeltaTime = 0.f;
		m_ElapsedTime -= m_FPSIntervalSeconds;
	}
	
}

void dae::FPSComponent::Render() const
{
}

void dae::FPSComponent::SetOwner(std::shared_ptr<GameObject>& pOwner)
{
	m_pOwner = pOwner;
	std::shared_ptr<TextComponent> possibleTextComponent = pOwner->GetComponent<TextComponent>();
	if (possibleTextComponent != nullptr)
	{
		m_pTextComponent = possibleTextComponent;
	}
}

void dae::FPSComponent::SetPosition(float x, float y)
{
	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->SetPosition(x, y);
	}
}

