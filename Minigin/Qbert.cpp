#include "MiniginPCH.h"
#include "Qbert.h"
#include "QbertObserver.h"

void dae::Qbert::Update()
{
}

void dae::Qbert::Render() const
{
}

void dae::Qbert::Die()
{
	if (m_Lives > 0)
	{
		m_Lives--;
	}
	for (std::shared_ptr<QbertObserver> pObserver: m_pObservers)
	{
		pObserver->Died();
	}
	
}

void dae::Qbert::ChangeTile()
{
	for (std::shared_ptr<QbertObserver> pObserver : m_pObservers)
	{
		pObserver->ChangeTile();
	}
}

void dae::Qbert::AddObserver(const std::shared_ptr<QbertObserver>& pObserver)
{
	m_pObservers.push_back(pObserver);
	
}

void dae::Qbert::RemoveObserver(const std::shared_ptr<QbertObserver>& pObserver)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver), m_pObservers.end());
}

int dae::Qbert::GetLives() const
{
	return m_Lives;
}

dae::Qbert::Qbert(const Qbert& other)
{
	std::copy(other.m_pObservers.begin(), other.m_pObservers.end(), std::back_inserter(m_pObservers));
	m_Lives = other.m_Lives;
}
