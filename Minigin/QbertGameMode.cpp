#include "MiniginPCH.h"
#include "QbertGameMode.h"

#include "GameObject.h"
#include "Observer.h"
#include "TextComponent.h"

void dae::QbertGameMode::OnNotify(GameObject& gameOject, Event event)
{
	switch (event)
	{
	case Event::PlayerDied:
		gameOject.GetComponent<TextComponent>()->SetText("Player died");
		break;
	}
	
}
