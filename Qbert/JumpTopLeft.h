#pragma once
#include "Command.h"

namespace dae
{
	class JumpTopLeft: public Command
	{
	public:
		JumpTopLeft(const std::shared_ptr<GameObject>& gameObject);
		void execute() override;
	};
	
}
