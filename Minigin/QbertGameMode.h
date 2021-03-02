#pragma once
#include "Observer.h"

namespace dae
{
	class QbertGameMode :
		public Observer
	{
	public:
		
		void OnNotify(GameObject& gameOject, Event event) override;
	private:
	};
}


