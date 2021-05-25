#pragma once
#include "Command.h"

namespace dae
{
	
	class JumpTopRight : public Command
	{
	public:
		JumpTopRight(const std::shared_ptr<GameObject>& pGameObject);
		void execute() override;
	};

}
