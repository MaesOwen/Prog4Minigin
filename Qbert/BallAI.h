#pragma once
#include "Component.h"
#include "CrossJump.h"

namespace dae
{
	class BallAI: public dae::Component
	{
	public:
		BallAI();
		void Update() override;
		void Render() const override;
		void SetOwner(dae::GameObject* pOwner) override;
		void StartAI();

	private:
		bool m_IsActive;
		float m_ElapsedSeconds;
		float m_TimeBetweenAIDecisions;
		CrossJump* m_pCrossJump;

		void JumpRandomDirectionDownwards();
		void BottomReached();
	};
	
}
