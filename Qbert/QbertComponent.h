#pragma once
#include "Component.h"
#include "QbertSubject.h"

namespace dae
{
	class QbertObserver;
	class QbertComponent final: public Component, public QbertSubject
	{
	public:
		void Update() override;
		void Render() const override;
		void SetOwner(GameObject* pOwner) override;
		void Die() override;
		void ChangeTile() override;
		int GetLives() const;

		QbertComponent(int qbertWidth, int qbertHeight);
		virtual ~QbertComponent() = default;
		QbertComponent(const QbertComponent& other);
		QbertComponent(QbertComponent&& other) = delete;
		QbertComponent& operator=(const QbertComponent& other) = delete;
		QbertComponent& operator=(QbertComponent&& other) = delete;

	private:
		int m_Lives{3};
		int m_QbertWidth;
		int m_QbertHeight;
	};

}
