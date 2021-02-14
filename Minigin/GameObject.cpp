#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject(std::shared_ptr<RenderComponent>& pRenderComponent, std::shared_ptr<TextComponent>& pTextComponent, std::shared_ptr<FPSComponent>& pFpsComponent)
	:m_pRenderComponent(pRenderComponent)
	,m_pTextComponent(pTextComponent)
	,m_pFPSComponent(pFpsComponent)
{
}

dae::GameObject::GameObject(std::shared_ptr<RenderComponent>& pRenderComponent)
	:m_pRenderComponent(pRenderComponent)
{
}

dae::GameObject::GameObject(std::shared_ptr<TextComponent>& pTextComponent)
	:m_pTextComponent(pTextComponent)
{
}

dae::GameObject::GameObject(std::shared_ptr<FPSComponent>& pFpsComponent)
	:m_pFPSComponent(pFpsComponent)
{
}


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	if (m_pFPSComponent != nullptr)
	{
		m_pFPSComponent->Update();
	}
	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	if (m_pRenderComponent != nullptr)
	{
		m_pRenderComponent->Render(m_Transform);
	}
	if (m_pTextComponent != nullptr)
	{
		m_pTextComponent->Render();
	}
	if (m_pFPSComponent != nullptr)
	{
		m_pFPSComponent->Render();
	}
	
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	if (m_pRenderComponent != nullptr)
	{
		m_pRenderComponent->SetTexture(filename);
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
