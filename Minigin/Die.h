#pragma once
#include "Command.h"

class Die:public dae::Command
{
public:
	void execute(dae::GameObject& gameObject) override;
};
