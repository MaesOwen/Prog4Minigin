#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"


bool dae::InputManager::ProcessInput()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&m_CurrentControllerState, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(0, &m_CurrentControllerState);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_KeyPressed = e.key.keysym.sym;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}
	HandleInput();
	
	m_LastControllerState = m_CurrentControllerState;

	

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{

	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

void dae::InputManager::BindControl(const std::string& name, const std::string& key, ControllerButton controllerButton, const std::shared_ptr<Command>& command)
{
	if (name != " " && command)
	{
		std::string nameGA{ name };
		nameGA[0] = char(std::toupper(nameGA[0]));

		auto it = m_pGameActionsMap.find(nameGA);
		if (it != m_pGameActionsMap.end())
		{
			it->second->command = command;
			it->second->controllerButton = controllerButton;
			it->second->keycode = SDL_GetKeyFromName(key.c_str());
			std::cout << "GameAction(" << nameGA << ") modified" << std::endl;
		}
		else
		{
			auto newGA = std::make_shared<GameAction>();
			newGA->name = nameGA;
			newGA->command = command;
			newGA->controllerButton = controllerButton;
			newGA->keycode = SDL_GetKeyFromName(key.c_str());
			m_pGameActionsMap.insert(std::pair<std::string, std::shared_ptr<GameAction>>(newGA->name, newGA));
			std::cout << "GameAction(" << nameGA << ") inserted" << std::endl;
		}
		std::cout << "GameActions size: " << m_pGameActionsMap.size() << std::endl;
	}
}

void dae::InputManager::BindControl(const std::string& name, const std::string& key, const std::shared_ptr<Command>& command)
{
	BindControl(name, key, ControllerButton::None, command);
}

void dae::InputManager::BindControl(const std::string& name, ControllerButton controllerButton, const std::shared_ptr<Command>& command)
{
	BindControl(name, nullptr, controllerButton, command);
}

void dae::InputManager::PrintControls()
{
	printf("%s \n", "Controls: ");
	for (auto& it : m_pGameActionsMap)
	{
		printf("%*s \n", 5, it.first.c_str());
		printf("%*s", 10, "Keybind: ");
		printf("%s \n", SDL_GetKeyName(it.second->keycode));
	}
}


void dae::InputManager::HandleInput()
{
	for (auto& it : m_pGameActionsMap)
	{
		if (m_KeyPressed == it.second->keycode)
		{
			it.second->command->execute();
		}
		else if(m_LastControllerState.Gamepad.wButtons != m_CurrentControllerState.Gamepad.wButtons
			&& IsPressed(it.second->controllerButton))
		{
			it.second->command->execute();
		}
	}

	m_KeyPressed = NULL;
	
}

void dae::InputManager::HandleKeyInput(SDL_Keycode keycode)
{
	for (auto& it : m_pGameActionsMap)
	{
		if (keycode == it.second->keycode)
		{
			std::cout << "Execute command" << std::endl;
			it.second->command->execute();
		}
	}
}

