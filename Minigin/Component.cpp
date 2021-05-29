#include "MiniginPCH.h"
#include "Component.h"

void dae::Component::SetOwner(std::shared_ptr<GameObject>& pOwner)
{
	m_pOwner = pOwner;

}

//std::shared_ptr<dae::GameObject>& dae::Component::GetOwner() const
//{
//	auto shared = m_pOwner.lock();
//	return shared;
//}
