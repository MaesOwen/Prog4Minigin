#pragma once
#include <memory>

#include "Command.h"

namespace dae
{
	class JumpBottomLeft: public Command
	{
	public:
		JumpBottomLeft(const std::shared_ptr<GameObject>& gameObject);
		void execute() override;
	};
}
