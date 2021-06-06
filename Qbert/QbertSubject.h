#pragma once
#include <memory>
#include <vector>

namespace dae {
	class QbertObserver;
	class QbertSubject
	{
	public:
		virtual void Die() = 0;
		virtual void FallOff() = 0;
		virtual void ChangeTile() = 0;
		virtual void AddObserver(const std::shared_ptr<QbertObserver>& pObserver);
		virtual void RemoveObserver(const std::shared_ptr<dae::QbertObserver>& pObserver);

	protected:
		std::vector<std::shared_ptr<QbertObserver>> m_pObservers;
	};
}


