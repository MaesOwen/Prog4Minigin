#pragma once
#include <SDL_keycode.h>
#include <XInput.h>
#include "Singleton.h"
#include <unordered_map>

namespace dae
{
	class Command;

	enum class ControllerButton
	{
		None,
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
		
		void BindControl(const std::string& name, const std::string& key, ControllerButton controllerButton, const std::shared_ptr<Command>& command);
		void BindControl(const std::string& name, const std::string& key, const std::shared_ptr<Command>& command);
		void BindControl(const std::string& name, ControllerButton controllerButton, const std::shared_ptr<Command>& command);

		void PrintControls();
	
	private:
		struct GameAction
		{
			std::string name;
			std::shared_ptr<Command> command;
			SDL_Keycode keycode;
			ControllerButton controllerButton;
		};
		std::unordered_map<std::string, std::shared_ptr<GameAction>> m_pGameActionsMap;
		XINPUT_STATE m_CurrentControllerState{};
		XINPUT_STATE m_LastControllerState{};
		SDL_Keycode m_KeyPressed{};
		std::shared_ptr<Command> m_pButtonX;
		std::shared_ptr<Command> m_pButtonY;
		std::shared_ptr<Command> m_pButtonA;
		std::shared_ptr<Command> m_pButtonB;

		
		
		void HandleInput();
		void HandleKeyInput(SDL_Keycode keycode);
	};

}
