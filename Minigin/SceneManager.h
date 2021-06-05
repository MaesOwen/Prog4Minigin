#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void Update();
		void Render();
		void SetScene(int sceneNr);
		void NextScene();
		void PrevScene();
		std::shared_ptr<Scene> GetActiveScene();
	
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		int m_CurrentSceneIndex;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		//std::weak_ptr<Scene> m_CurrentScene;
	};
}
