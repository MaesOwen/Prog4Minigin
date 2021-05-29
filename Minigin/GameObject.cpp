#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"


dae::GameObject::GameObject()
{
	AddComponent(std::make_shared<TransformComponent>());
}


dae::GameObject::GameObject(const GameObject & other)
{
	std::copy(other.m_pComponents.begin(), other.m_pComponents.end(), std::back_inserter(m_pComponents));
}

void dae::GameObject::MoveChildrenPosition(float x, float y, float z)
{
	for(std::weak_ptr<GameObject> weakChildGO: m_pChildrenGOs)
	{
		if (auto sharedChildGO = weakChildGO.lock())
			if (auto transform = sharedChildGO->GetTransformComponent())
				transform->AddToPosition(x, y, z);
	}
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
		
		if (m_pChildrenGOs.size() > 0)
		{
			MoveChildrenPosition(x, y, z);
		}
	}
	
}

void dae::GameObject::SetPosition(const glm::vec3& pos)
{
	SetPosition(pos.x, pos.y, pos.z);
}

std::shared_ptr<dae::TransformComponent> dae::GameObject::GetTransformComponent() const
{
	return std::dynamic_pointer_cast<TransformComponent>(m_pComponents.back());
}



void dae::GameObject::AddComponent(const std::shared_ptr<Component>& pComponent)
{
	//auto sharedGO = std::make_shared<GameObject>(*this);
	pComponent->SetOwner(this);
	m_pComponents.push_front(pComponent);	
}

void dae::GameObject::AddParent(std::shared_ptr<GameObject>& parentGO)
{
	m_pParentGO = parentGO;

}

void dae::GameObject::AddChild(std::shared_ptr<GameObject>& childGO)
{
	bool isDuplicate = false;
	//isDuplicate = find(begin(m_pChildrenGOs), end(m_pChildrenGOs), childGO) == std::end(m_pChildrenGOs);

	for (std::weak_ptr<GameObject> weakChildGO: m_pChildrenGOs)
	{
		if(auto sharedChildGO = weakChildGO.lock())
		{
			if (sharedChildGO == childGO)
			{
				isDuplicate = true;
				break;
			}	
		}
	}

	if(!isDuplicate)
		m_pChildrenGOs.push_back(childGO);
}

std::vector<std::weak_ptr<dae::GameObject>>& dae::GameObject::GetChildren()
{
	return m_pChildrenGOs;
}

std::weak_ptr<dae::GameObject>& dae::GameObject::GetParent()
{
	return m_pParentGO;
}

const int dae::GameObject::GetChildCount() const
{
	int childCount = 0;
	for(std::weak_ptr<GameObject> childGO: m_pChildrenGOs)
	{
		childCount++;
	}
	return childCount;
}
