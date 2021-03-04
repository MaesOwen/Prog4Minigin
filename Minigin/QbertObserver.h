#pragma once


namespace dae
{
	class GameObject;
	class QbertObserver
	{
	public:
		virtual ~QbertObserver() = default;
		virtual void Died() = 0;
		virtual void ChangeTile() = 0;

	};

}
