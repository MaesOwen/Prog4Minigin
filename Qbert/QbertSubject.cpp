#include "QbertSubject.h"
#include "MiniginPCH.h"
#include "QbertObserver.h"

void dae::QbertSubject::AddObserver(const std::shared_ptr<QbertObserver>& pObserver)
{
	m_pObservers.push_back(pObserver);
}

void dae::QbertSubject::RemoveObserver(const std::shared_ptr<dae::QbertObserver>& pObserver)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver), m_pObservers.end());
}
