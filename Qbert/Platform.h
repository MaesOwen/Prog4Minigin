#pragma once
#include "Component.h"
#include <glm/vec3.hpp>

namespace dae {
	class Qbert;
	class Sprite;
	class Platform : public Component
	{
	public:
		struct PlatFormCoords
		{
			int row;
			int col;

			friend bool operator<(const PlatFormCoords& pc1, const PlatFormCoords& pc2) {
				return pc1.row < pc2.row || (pc1.row == pc2.row && pc1.col < pc2.col);
			}

		};

		Platform(PlatFormCoords platform, int maxNrOfColorChanges, bool doesJumpingAgainReset = false);
		void Update() override;
		void Render() const override;
		void JumpOn(std::shared_ptr<GameObject>& gameObject);
		void JumpOn(GameObject* gameObject);
		void JumpOff(std::shared_ptr<GameObject>& gameObject);
		const PlatFormCoords& GetPlatFormCoords();
		const glm::vec3& GetTopSidePos();
		void SetTopSidePos(const float x, const float y, const float z);
		std::vector<std::weak_ptr<GameObject>>& GetGameObjectsOnPlatform();
		bool IsTargetColor() const;

	private:
		int m_CurrNrOfColorChanges;
		int m_MaxNrOfColorChanges;
		PlatFormCoords m_PlatformCoords;
		bool m_DoesJumpingAgainReset;
		std::vector<std::weak_ptr<GameObject>> m_pGameObjectsOnPlatform;
		glm::vec3 m_TopSidePos;
		glm::vec3 m_LeftSidePos;
		glm::vec3 m_RightSidePos;
		bool m_AreSidesPosSet;
		
		

	};
}


