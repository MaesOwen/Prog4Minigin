#pragma once
#include "Command.h"

namespace dae
{
	class Die:public dae::Command
	{
	public:
		Die(const std::shared_ptr<GameObject>& pGameObject);
		void execute() override;

	};
	
}
