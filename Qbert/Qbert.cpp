// Qbert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once



//#include <iostream>
#include <iostream>
#include <Minigin.h>
#include <string>
#include <vector>
#include <memory>
#include <Windows.h>
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextComponent.h"

#include "AudioLocator.h"
#include "BallAI.h"
#include "ChangeTile.h"
#include "Coily.h"
#include "CoilyAI.h"
#include "CrossJump.h"
#include "Die.h"
#include "FPSComponent.h"
#include "InputManager.h"
#include "JumpBottomLeft.h"
#include "JumpBottomRight.h"
#include "JumpTopLeft.h"
#include "JumpTopRight.h"
#include "LivesDisplay.h"
#include "Platform.h"
#include "QbertSounds.h"
#include "ScoreDisplay.h"
#include "SDL2AudioSystem.h"
#include "Sprite.h"
#include "QbertComponent.h"
#include "QbertSprite.h"

using namespace dae;
using namespace std;
void LoadGame();
std::shared_ptr<GameObject> CreateLevelPlatform(int beginPosX, int beginPosY, int platformWidth, int platformHeight, dae::Scene& scene);


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
	
	//sound
	SDL2AudioSystem* pSoundSystem = new SDL2AudioSystem(false);
	AudioLocator::GetInstance().ProvideAudioSystem(pSoundSystem);

	int deathSoundId = dae::AudioLocator::GetInstance().GetAudioSystem()->Load("../Data/death.wav");
	int landQbertSoundId = dae::AudioLocator::GetInstance().GetAudioSystem()->Load("../Data/land.wav");
	
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

	//fps component
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	tc = std::make_shared<TextComponent>("55 FPS", font);
	auto fc = std::make_shared<FPSComponent>();
	go = std::make_shared<GameObject>();
	go->AddComponent(tc);
	go->AddComponent(fc);
	std::shared_ptr<TextComponent> textComp = go->GetComponent<TextComponent>();
	if (textComp)
	{
		textComp->SetTextColor(255, 255, 0);
		textComp->SetPosition(5, 5);
	}
	scene.Add(go);

	//level try out
	int beginPosX = 320; //middle of screen
	int beginPosY = 100;
	int platformWidth = 64;
	int platformHeight = 48;

	auto hexGridGO = CreateLevelPlatform(beginPosX, beginPosY, platformWidth, platformHeight, scene);
	

	//Qbert
	int qbertWidth = 30;
	int qbertHeight = 30;

	
	auto qbertGO = std::make_shared<GameObject>();

	auto qsc = make_shared<QbertSounds>();
	qsc->SetQbertSound(QbertSounds::land, landQbertSoundId);
	qbertGO->AddComponent(qsc);
	
	/*auto sc = std::make_shared<Sprite>(qbertWidth, qbertWidth);
	
	qbertGO->AddComponent(sc);*/
	
	auto qb = make_shared<QbertComponent>(qbertWidth, qbertHeight);
	qbertGO->AddComponent(qb);

	auto cc = make_shared<CrossJump>();
	cc->SetPlatformMap(hexGridGO);
	qbertGO->AddComponent(cc);
	qbertGO->GetTransformComponent()->SetPosition(float(beginPosX), float(beginPosY), 0);

	

	//Lives hud 1
	auto livesGO = make_shared<GameObject>();
	livesGO->GetTransformComponent()->SetPosition(50, 250, 0);
	tc = make_shared<TextComponent>("Lives: 3", font);
	livesGO->AddComponent(tc);
	auto ld = std::make_shared<LivesDisplay>(livesGO);
	tc->SetPosition(0, 120);
	tc->SetTextColor(255, 0, 0);
	qb->AddObserver(ld);

	ld->SetQbert(qb);

	//Score hud1
	auto scoreGO = make_shared<GameObject>();
	scoreGO->GetTransformComponent()->SetPosition(50, 250, 0);
	tc = make_shared<TextComponent>("Score: 0", font);
	scoreGO->AddComponent(tc);
	auto sd = std::make_shared<ScoreDisplay>(scoreGO);
	tc->SetPosition(0, 140);
	tc->SetTextColor(0, 255, 0);
	qb->AddObserver(sd);

	scene.Add(qbertGO);
	scene.Add(livesGO);
	scene.Add(scoreGO);


	//coily
	int coilyWidth = 30;
	int coilyHeight = 62;

	auto coilyGO = make_shared<GameObject>();
	auto coily = make_shared<Coily>(coilyWidth, coilyHeight);

	auto jump = make_shared<CrossJump>();
	jump->SetPlatformMap(hexGridGO);

	coilyGO->AddComponent(coily);
	coilyGO->AddComponent(jump);

	coilyGO->GetTransformComponent()->SetPosition(float(beginPosX), float(beginPosY), 0);
	coilyGO->GetComponent<BallAI>()->StartAI();
	coilyGO->GetComponent<CoilyAI>()->SetTarget(qbertGO.get());

	scene.Add(coilyGO);
	
	
	
	
	
	

	//input player1
	InputManager::GetInstance().BindControl("TopLeftJumpP1", "W", ControllerButton::ButtonY, make_shared<JumpTopLeft>(qbertGO));
	InputManager::GetInstance().BindControl("TopRightJumpP1", "D", ControllerButton::ButtonB, make_shared<JumpTopRight>(qbertGO));
	InputManager::GetInstance().BindControl("BottomLeftJumpP1", "A", ControllerButton::ButtonX, make_shared<JumpBottomLeft>(qbertGO));
	InputManager::GetInstance().BindControl("BottomRightJumpP1", "S", ControllerButton::ButtonA, make_shared<JumpBottomRight>(qbertGO));

	//input player2
	InputManager::GetInstance().BindControl("TopLeftJumpP2", "I", ControllerButton::ButtonY, make_shared<JumpTopLeft>(coilyGO));
	InputManager::GetInstance().BindControl("TopRightJumpP2", "L", ControllerButton::ButtonB, make_shared<JumpTopRight>(coilyGO));
	InputManager::GetInstance().BindControl("BottomLeftJumpP2", "J", ControllerButton::ButtonX, make_shared<JumpBottomLeft>(coilyGO));
	InputManager::GetInstance().BindControl("BottomRightJumpP2", "K", ControllerButton::ButtonA, make_shared<JumpBottomRight>(coilyGO));
	
	//InputManager::GetInstance().BindControl("PointsPlayer1", "W", ControllerButton::ButtonA, make_shared<Die>(qbertGO));
	//InputManager::GetInstance().BindControl("DeadPlayer1", "S", ControllerButton::ButtonB, make_shared<ChangeTile>(qbertGO));

	
	
	
	
	//ShowControls
	InputManager::GetInstance().PrintControls();

	
}

std::shared_ptr<GameObject> CreateLevelPlatform(int beginPosX, int beginPosY, int platformWidth, int platformHeight, dae::Scene& scene)
{
	auto hexGridGO = make_shared<GameObject>();
	int nrOfBlocksPerRow = 1;
	for (int row = 0; row < 7; row++)
	{
		nrOfBlocksPerRow = row + 1;
		beginPosX -= (platformWidth / 2);

		for (int col = 0; col < nrOfBlocksPerRow; col++)
		{
			auto platformGO = std::make_shared<GameObject>();
			auto sc = std::make_shared<Sprite>(platformWidth, platformWidth);
			auto pc = std::make_shared<Platform>(Platform::PlatFormCoords{row, col}, 1);
			auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
			string test = std::to_string(row) + ", " + std::to_string(col);
			auto tc = std::make_shared<TextComponent>(test, font);

			platformGO->AddComponent(sc);
			platformGO->AddComponent(pc);
			platformGO->AddComponent(tc);
			
			

			tc->SetPosition(platformWidth / 2.f, platformHeight / 4.f);
			tc->SetTextColor(255, 255, 255);
			sc->SetTexture("sprites.png");
			sc->AddFrame(Sprite::Frame{ 0,224, 31, 31 });
			sc->AddFrame(Sprite::Frame{ 0,192, 31, 31 });
			sc->AddFrame(Sprite::Frame{ 0,160, 31, 31 });

			const float posX{ float(beginPosX + platformWidth * col) };
			const float posY{ float(beginPosY + platformHeight * row) };
			
			pc->SetTopSidePos(posX + platformWidth/2.f, posY + platformHeight/5.f*2.f, 0);

			platformGO->SetPosition(posX, posY, 0.f);
			scene.Add(platformGO);

			hexGridGO->AddChild(platformGO);
		}

	}
	return hexGridGO;
}
