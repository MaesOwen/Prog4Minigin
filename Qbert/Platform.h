#pragma once
#include "Component.h"
#include <glm/vec3.hpp>

namespace dae {
	class Sprite;
	class Platform : public Component
	{
	public:
		struct PlatFormCoords
		{
			int row;
			int col;
			glm::vec3 topSidePos;
			glm::vec3 leftSidePos;
			glm::vec3 rightSidePos;
		};

		Platform(PlatFormCoords platform, int maxNrOfColorChanges, bool doesJumpingAgainReset = false);
		void Update() override;
		void Render() const override;
		void JumpOn(std::shared_ptr<GameObject>& gameObject);
		void JumpOff(std::shared_ptr<GameObject>& gameObject);
		const PlatFormCoords& GetPlatFormCoords();
		std::vector<std::weak_ptr<GameObject>>& GetGameObjectsOnPlatform();

	private:
		int m_CurrNrOfColorChanges;
		int m_MaxNrOfColorChanges;
		PlatFormCoords m_PlatformCoords;
		bool m_DoesJumpingAgainReset;
		std::vector<std::weak_ptr<GameObject>> m_pGameObjectsOnPlatform;



	};
}


