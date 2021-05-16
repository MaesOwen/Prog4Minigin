#pragma once
#include "Singleton.h"
//#include <chrono>

namespace dae
{
	class TimeMinigin final: public Singleton<TimeMinigin>
	{
	public:
		const float& GetDeltaTime() const;
		void SetDeltaTime(const float deltaTime);
	private:
		friend class Singleton<TimeMinigin>;
		TimeMinigin() = default;
		float m_DeltaTime;
	}; 
}
