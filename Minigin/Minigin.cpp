#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "FPSComponent.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "RenderComponent.h"
#include "TextComponent.h"

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
	//rc->SetTexture("background.jpg");
	go->GetComponent<RenderComponent>()->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	rc = std::make_shared<RenderComponent>();
	go->AddComponent(rc);
	go->GetComponent<RenderComponent>()->SetTexture("logo.png");
	//rc->SetTexture("logo.png");
	go->SetPosition(216, 180, 0.f);
	scene.Add(go);

	
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tc = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	go = std::make_shared<GameObject>();
	go->AddComponent(tc);
	go->GetComponent<TextComponent>()->SetPosition(80, 20);
	scene.Add(go);

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
