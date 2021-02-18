#include "MiniginPCH.h"
#include "Component.h"

void dae::Component::SetOwner(std::shared_ptr<GameObject> pOwner)
{
	m_pOwner = pOwner;
}
