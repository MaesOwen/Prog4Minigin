#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "audio.c"
#include "AudioLocator.h"
#include "SDL2AudioSystem.h"
#include "ChangeTile.h"
#include "Die.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "LivesDisplay.h"
#include "Qbert.h"
#include "Scene.h"
#include "Time.h"
#include "RenderComponent.h"
#include "ScoreDisplay.h"
#include "TextComponent.h"
#include "TransformComponent.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	
	Renderer::GetInstance().Init(m_Window);
	
	initAudio(); 
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//sound
	SDL2AudioSystem* pSoundSystem = new SDL2AudioSystem(false);
	AudioLocator::GetInstance().ProvideAudioSystem(pSoundSystem);

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

	//Qbert1
	auto qbertGO = std::make_shared<GameObject>();
	rc = std::make_shared<RenderComponent>();
	rc->SetTexture("qbert.png");
	qbertGO->AddComponent(rc);
	auto qb = make_shared<Qbert>();

	qbertGO->AddComponent(qb);
	qbertGO->GetTransformComponent()->SetPosition(50, 200, 0);

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
	std::cout << "Qbert1 ref count " << qb.use_count() << std::endl;

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

	//Qbert2
	auto qbertGO2 = make_shared<GameObject>();
	rc = make_shared<RenderComponent>();
	rc->SetTexture("qbert.png");
	qbertGO2->AddComponent(rc);
	qb = make_shared<Qbert>();

	qbertGO2->AddComponent(qb);
	qbertGO2->GetTransformComponent()->SetPosition(420, 200, 0);

	//Lives hud 2
	livesGO = make_shared<GameObject>();
	livesGO->GetTransformComponent()->SetPosition(420, 250, 0);
	tc = make_shared<TextComponent>("Lives: 3", font);
	livesGO->AddComponent(tc);
	ld = std::make_shared<LivesDisplay>(livesGO);
	tc->SetPosition(0, 120);
	tc->SetTextColor(255, 0, 0);
	qb->AddObserver(ld);
	ld->SetQbert(qb);

	std::cout << "Qbert2 ref count " << qb.use_count() << std::endl;

	//Score hud 2
	scoreGO = make_shared<GameObject>();
	scoreGO->GetTransformComponent()->SetPosition(420, 250, 0);
	tc = make_shared<TextComponent>("Score: 0", font);
	scoreGO->AddComponent(tc);
	sd = std::make_shared<ScoreDisplay>(scoreGO);
	tc->SetPosition(0, 140);
	tc->SetTextColor(0, 255, 0);
	qb->AddObserver(sd);

	scene.Add(qbertGO2);
	scene.Add(livesGO);
	scene.Add(scoreGO);

	//input
	InputManager::GetInstance().BindControl("PointsPlayer1", "W", ControllerButton::ButtonA, make_shared<Die>(qbertGO));
	InputManager::GetInstance().BindControl("DeadPlayer1", "S", ControllerButton::ButtonB, make_shared<ChangeTile>(qbertGO));
	InputManager::GetInstance().BindControl("PointsPlayer2", "E", ControllerButton::ButtonX, make_shared<Die>(qbertGO2));
	InputManager::GetInstance().BindControl("DeadPlayer2", "D", ControllerButton::ButtonY, make_shared<ChangeTile>(qbertGO2));

	//ShowControls
	InputManager::GetInstance().PrintControls();

	//Sound
	dae::AudioLocator::GetInstance().GetAudioSystem()->Load("../Data/death.wav");
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	AudioLocator::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	endAudio();
	SDL_Quit();
}

void dae::Minigin::Run()
{
	//Initialize();

	// tell the resource manager where he can find the game data
	//ResourceManager::GetInstance().Init("../Data/");

	//LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;

		auto lastTime = high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			Time::GetInstance().SetDeltaTime(std::chrono::duration<float>(currentTime - lastTime).count());
			
			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();

			lastTime = currentTime;
			
			const auto sleepTime = lastTime + milliseconds(MsPerFrame) - high_resolution_clock::now();
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
