#include "MiniginPCH.h"
#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"


void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_pOwner->GetTransformComponent()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}
