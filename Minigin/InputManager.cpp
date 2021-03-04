#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

#include "Command.h"


bool dae::InputManager::ProcessInput()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(0, &m_CurrentState);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}
	HandleInput();
	
	m_LastState = m_CurrentState;

	

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{

	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

void dae::InputManager::BindControl(ControllerButton controllerButton, const std::shared_ptr<Command>& command)
{
	switch (controllerButton)
	{
	case ControllerButton::ButtonX:
		m_pButtonX = command;
		break;
	case ControllerButton::ButtonY:
		m_pButtonY = command;
		break;
	case ControllerButton::ButtonA:
		m_pButtonA = command;
	case ControllerButton::ButtonB:
		m_pButtonB = command;
		break;
		break;
	default:
		break;
	}
}


void dae::InputManager::HandleInput()
{
	if (m_LastState.Gamepad.wButtons != m_CurrentState.Gamepad.wButtons)
	{
		if (IsPressed(ControllerButton::ButtonX))
		{
			if (m_pButtonX)
				m_pButtonX->execute();
		}
		if (IsPressed(ControllerButton::ButtonY))
		{
			if (m_pButtonY)
				m_pButtonY->execute();
		}
		if (IsPressed(ControllerButton::ButtonA))
		{
			if (m_pButtonA)
				m_pButtonA->execute();
		}
		if (IsPressed(ControllerButton::ButtonB))
		{
			if (m_pButtonB)
				m_pButtonB->execute();
		}
	}
	
}

