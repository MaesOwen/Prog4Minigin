// Qbert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <Minigin.h>

#include <string>
#include <vector>
#include <memory>

#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextComponent.h"

#include "AudioLocator.h"
#include "SDL2AudioSystem.h"

using namespace dae;
using namespace std;
void LoadGame();



int main()
{
	dae::Minigin engine;
	engine.Initialize();
	LoadGame();
	engine.Run();

	return 0;
}

void LoadGame()
{
	//init resource manager
	ResourceManager::GetInstance().Init("../Data/");
	
	////sound
	//SDL2AudioSystem* pSoundSystem = new SDL2AudioSystem(false);
	//AudioLocator::GetInstance().ProvideAudioSystem(pSoundSystem);
	
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	

	auto go = std::make_shared<GameObject>();
	auto rc = std::make_shared<RenderComponent>();
	go->AddComponent(rc);
	go->GetComponent<RenderComponent>()->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	rc = std::make_shared<RenderComponent>();
	go->AddComponent(rc);
	go->GetComponent<RenderComponent>()->SetTexture("logo.png");
	go->SetPosition(216, 180, 0.f);
	scene.Add(go);


	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tc = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	go = std::make_shared<GameObject>();
	go->AddComponent(tc);
	go->GetComponent<TextComponent>()->SetPosition(80, 20);
	scene.Add(go);
}
