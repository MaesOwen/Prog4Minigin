#pragma once
#include "Command.h"

namespace dae
{
	class JumpBottomRight: public dae::Command
	{
	public:
		JumpBottomRight(const std::shared_ptr<GameObject>& pGameObject);
		void execute() override;
	};
}
