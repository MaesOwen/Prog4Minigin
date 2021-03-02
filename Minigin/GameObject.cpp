#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"


void dae::GameObject::AddObserver(std::shared_ptr<Observer> pObserver)
{
	m_pObservers.push_back(pObserver);
}

dae::GameObject::GameObject()
{
	AddComponent(std::make_shared<TransformComponent>());
}


dae::GameObject::GameObject(const GameObject & other)
{
	std::copy(other.m_pComponents.begin(), other.m_pComponents.end(), std::back_inserter(m_pComponents));
}


void dae::GameObject::Update()
{
	for (auto& pComponent: m_pComponents)
	{
		pComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::SetPosition(const float x, const float y, const float z)
{
	std::shared_ptr<TransformComponent> pTransform = GetTransformComponent();
	if (pTransform != nullptr)
	{
		pTransform->SetPosition(x, y, z);
	}
}

std::shared_ptr<dae::TransformComponent> dae::GameObject::GetTransformComponent() const
{
	return std::dynamic_pointer_cast<TransformComponent>(m_pComponents.back());
}



void dae::GameObject::AddComponent(std::shared_ptr<Component> pComponent)
{
	pComponent->SetOwner(std::make_shared<GameObject>(*this));
	m_pComponents.push_front(pComponent);	
}
