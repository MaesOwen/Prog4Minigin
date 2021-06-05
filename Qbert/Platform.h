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
		void JumpOff(GameObject* gameObject);
		std::shared_ptr<GameObject> GetCurrentGOOnPlatform() const;
		const PlatFormCoords& GetPlatFormCoords();
		const glm::vec3& GetTopSidePos();
		void SetTopSidePos(const float x, const float y, const float z);
		bool IsTargetColor() const;

	private:
		int m_CurrNrOfColorChanges;
		int m_MaxNrOfColorChanges;
		PlatFormCoords m_PlatformCoords;
		bool m_DoesJumpingAgainReset;
		std::shared_ptr<GameObject> m_pCurrentGOOnPlatform;
		glm::vec3 m_TopSidePos;
		glm::vec3 m_LeftSidePos;
		glm::vec3 m_RightSidePos;
		bool m_AreSidesPosSet;
		
		void CheckIfQbertAndEnemiesCollide(GameObject* gameObject);
		
	};
}


