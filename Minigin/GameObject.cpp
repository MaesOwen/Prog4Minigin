#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"


dae::GameObject::GameObject()
	:m_Tag("Test")
	,m_IsActive(true)
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
	if(m_IsActive)
	{
		for (auto& pComponent : m_pComponents)
		{
			pComponent->Update();
		}
	}
	
}

void dae::GameObject::Render() const
{
	if(m_IsActive)
	{
		for (auto& pComponent : m_pComponents)
		{
			pComponent->Render();
		}
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
	pComponent->SetOwner(this);
	m_pComponents.push_front(pComponent);	
}

void dae::GameObject::SetTag(const std::string& newTag)
{
	m_Tag = newTag;
}

const std::string& dae::GameObject::GetTag() const
{
	return m_Tag;
}

void dae::GameObject::AddParent(GameObject* pParentGO)
{
	m_pParentGO = pParentGO;

}

void dae::GameObject::AddChild(std::shared_ptr<GameObject>& childGO)
{
	childGO->AddParent(this);
	
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

dae::GameObject* dae::GameObject::GetParent()
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

bool dae::GameObject::GetIsActive() const
{
	return m_IsActive;
}

void dae::GameObject::SetIsActive(bool isActive)
{
	m_IsActive = isActive;
	for(auto weakChildGO: m_pChildrenGOs)
	{
		if(auto sharedChildGO = weakChildGO.lock())
		{
			sharedChildGO->SetIsActive(isActive);
		}
	}
}
