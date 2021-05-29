#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

void dae::Component::SetOwner(std::shared_ptr<GameObject>& pOwner)
{
	m_pOwner = pOwner.get();
	//m_pSharedOwner = pOwner;
}

void dae::Component::SetOwner(GameObject* pOwner)
{
	m_pOwner = pOwner;
}

dae::GameObject* dae::Component::GetOwner() const
{
	return m_pOwner;
}
