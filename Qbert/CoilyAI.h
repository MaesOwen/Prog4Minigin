#pragma once
#include "Component.h"

class CrossJump;

namespace dae
{
	class CoilyAI: public Component
	{
	public:
		CoilyAI();
		void Update() override;
		void Render() const override;
		void SetTarget(GameObject* target);
		void SetActiveAI(bool isActive);

	private:
		GameObject* m_pTarget;
		CrossJump* m_pCrossJump;
		bool m_IsActiveAI;
		float m_ElapsedSeconds;
		float m_TimeBetweenAIDecisions;

		void MoveTowardsTarget();
	};
}
