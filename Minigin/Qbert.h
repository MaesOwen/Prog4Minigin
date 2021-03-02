#pragma once
#include "GameObject.h"
#include "InputManager.h"


namespace dae
{
	enum class ControllerButton;

	class Qbert final : public GameObject
	{
	public:
		void Die();
		void Update() override;
		void SetControls(ControllerButton dieButton, ControllerButton scoreButton);
	private:
		ControllerButton m_DieButton = ControllerButton::ButtonA;
		ControllerButton m_ScoreButton = ControllerButton::ButtonB;
	};

}
