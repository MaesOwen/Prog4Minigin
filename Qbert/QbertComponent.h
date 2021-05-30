#pragma once
#include "Component.h"

namespace dae
{
	class QbertObserver;
	class QbertComponent final: public Component
	{
	public:
		void Update() override;
		void Render() const override;
		void SetOwner(GameObject* pOwner) override;
		void Die();
		void ChangeTile();
		void AddObserver(const std::shared_ptr<QbertObserver>& pObserver);
		void RemoveObserver(const std::shared_ptr<QbertObserver>& pObserver);
		int GetLives() const;

		QbertComponent(int qbertWidth, int qbertHeight);
		virtual ~QbertComponent();
		QbertComponent(const QbertComponent& other);
		QbertComponent(QbertComponent&& other) = delete;
		QbertComponent& operator=(const QbertComponent& other) = delete;
		QbertComponent& operator=(QbertComponent&& other) = delete;

	private:
		int m_Lives{3};
		std::vector<std::shared_ptr<QbertObserver>> m_pObservers;
		int m_QbertWidth;
		int m_QbertHeight;
	};

}
