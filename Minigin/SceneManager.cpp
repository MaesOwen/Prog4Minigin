#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	m_Scenes.at(m_CurrentSceneIndex)->Update();
	/*for(auto& scene : m_Scenes)
	{
		scene->Update();
	}*/
}

void dae::SceneManager::Render()
{
	m_Scenes.at(m_CurrentSceneIndex)->Render();
	/*for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}*/
	
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetActiveScene()
{
	return  m_Scenes.at(m_CurrentSceneIndex);
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::SetScene(int sceneNr)
{
	if(0 <= sceneNr && sceneNr < int(m_Scenes.size()))
	{
		m_CurrentSceneIndex = sceneNr;
		//m_CurrentScene = m_Scenes.at(m_CurrentSceneIndex);
	}
}

void dae::SceneManager::NextScene()
{
	if(m_CurrentSceneIndex + 1 < int(m_Scenes.size()))
	{
		m_CurrentSceneIndex++;
		
	}else
	{
		m_CurrentSceneIndex = 0;
	}
	//m_CurrentScene = m_Scenes.at(m_CurrentSceneIndex);
}

void dae::SceneManager::PrevScene()
{
	if(m_CurrentSceneIndex - 1 > 0)
	{
		m_CurrentSceneIndex--;
	}else
	{
		m_CurrentSceneIndex = int(m_Scenes.size()) - 1;
	}
	//m_CurrentScene = m_Scenes.at(m_CurrentSceneIndex);
}
