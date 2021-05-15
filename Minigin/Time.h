#pragma once
#include "Singleton.h"
//#include <chrono>

namespace dae
{
	class Time final: public Singleton<Time>
	{
	public:
		const float& GetDeltaTime() const;
		void SetDeltaTime(const float deltaTime);
	private:
		friend class Singleton<Time>;
		Time() = default;
		float m_DeltaTime;
	}; 
}
