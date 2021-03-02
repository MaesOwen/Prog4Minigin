#pragma once
#include <XInput.h>
#include "Singleton.h"

namespace dae
{
	class Command;

	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
	private:
		XINPUT_STATE m_CurrentState{};
		XINPUT_STATE m_LastState{};
		
	};

}
