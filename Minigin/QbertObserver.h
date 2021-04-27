#pragma once


namespace dae
{
	class GameObject;
	class QbertObserver
	{
	public:
		virtual void Died() = 0;
		virtual void ChangeTile() = 0;

		QbertObserver() = default;
		virtual ~QbertObserver() = default;
		QbertObserver(const QbertObserver& other) = delete;
		QbertObserver(QbertObserver&& other) = delete;
		QbertObserver& operator=(const QbertObserver& other) = delete;
		QbertObserver& operator=(QbertObserver&& other) = delete;
	};

}
