#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "RenderComponent.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
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
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	auto rc = std::make_shared<RenderComponent>();
	go->AddComponent(rc);
	rc->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	rc = std::make_shared<RenderComponent>();
	go->AddComponent(rc);
	rc->SetTexture("logo.png");
	go->SetPosition(216, 180, 0.f);
	scene.Add(go);

	
	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto tc = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	////auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//tc->SetPosition(80, 20);
	//go = std::make_shared<GameObject>(tc);
	//scene.Add(go);

	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	//tc = std::make_shared<TextComponent>("55 FPS", font);
	//tc->SetTextColor(255, 255, 0);
	//tc->SetPosition(5, 5);
	//auto fc = std::make_shared<FPSComponent>(tc);
	//go = std::make_shared<GameObject>(fc);
	//scene.Add(go);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& timer = Time::GetInstance();

		bool doContinue = true;
		timer.Start();
		
		double lag = 0.0;
		
		while (doContinue)
		{
			lag += timer.GetDeltaTime(); 
			
			doContinue = input.ProcessInput();

			while (lag >= MsPerFrame)
			{
				sceneManager.Update();
				lag -= MsPerFrame;
			}
			
			renderer.Render();

			timer.Reset();
		}
	}

	Cleanup();
}
