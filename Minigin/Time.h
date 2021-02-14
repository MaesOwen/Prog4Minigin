#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Time final: public Singleton<Time>
	{
	public:
		void Start();
		void Reset();
		const double& GetDeltaTime() const;
	private:
		friend class Singleton<Time>;
		Time() = default;
		double m_DeltaTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_CurrentTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_PreviousTime;
	}; 
}
