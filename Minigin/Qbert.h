#pragma once
#include "Component.h"

namespace dae
{
	class QbertObserver;
	class Qbert final: public Component
	{
	public:
		void Update() override;
		void Render() const override;
		void Die();
		void ChangeTile();
		void AddObserver(const std::shared_ptr<QbertObserver>& pObserver);
		void RemoveObserver(const std::shared_ptr<QbertObserver>& pObserver);
		int GetLives() const;

		Qbert() = default;
		virtual ~Qbert() = default;
		Qbert(const Qbert& other);
		Qbert(Qbert&& other) = delete;
		Qbert& operator=(const Qbert& other) = delete;
		Qbert& operator=(Qbert&& other) = delete;

	private:
		int m_Lives{3};
		std::vector<std::shared_ptr<QbertObserver>> m_pObservers;
	};

}
