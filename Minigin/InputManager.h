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
		void BindControl(ControllerButton controllerButton, const std::shared_ptr<Command>& command);
	
	private:
		XINPUT_STATE m_CurrentState{};
		XINPUT_STATE m_LastState{};
		std::shared_ptr<Command> m_pButtonX;
		std::shared_ptr<Command> m_pButtonY;
		std::shared_ptr<Command> m_pButtonA;
		std::shared_ptr<Command> m_pButtonB;
		
		void HandleInput();
	};

}
