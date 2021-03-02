#include "MiniginPCH.h"
#include "Qbert.h"

#include "InputManager.h"
#include "Observer.h"


void dae::Qbert::Die()
{
	//send event to observer
	for (std::shared_ptr<Observer> pObserver: m_pObservers)
	{
		pObserver->OnNotify(*this, Event::PlayerDied);
	}
}

void dae::Qbert::Update()
{
	GameObject::Update();
	
	auto& input = dae::InputManager::GetInstance();
	if (input.IsPressed(m_DieButton))
	{
		Die();
	}
	
}

void dae::Qbert::SetControls(ControllerButton dieButton, ControllerButton scoreButton)
{
	m_DieButton = dieButton;
	m_ScoreButton = scoreButton;
}
