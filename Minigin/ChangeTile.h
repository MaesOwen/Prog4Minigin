#pragma once
#include "Command.h"

namespace dae
{
	class ChangeTile: public Command
	{
	public:
		ChangeTile(const std::shared_ptr<GameObject>& pGameObject);
		void execute() override;
	};
}
