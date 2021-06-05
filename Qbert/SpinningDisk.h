#pragma once

#include <glm/detail/type_vec3.hpp>

#include "Component.h"

namespace dae {
	class TransformComponent;

	class SpinningDisk : public Component
	{
	public:
		SpinningDisk(int diskWidth, int diskHeight);
		void Update() override;
		void Render() const override;
		void SetOwner(GameObject* pOwner) override;
		void MoveQbertToPos(const glm::vec3& newPos, GameObject* qbertGO);

		~SpinningDisk() = default;
		SpinningDisk(const SpinningDisk& other) = delete;
		SpinningDisk(SpinningDisk&& other) = delete;
		SpinningDisk& operator=(const SpinningDisk& other) = delete;
		SpinningDisk& operator=(SpinningDisk&& other) = delete;


	private:
		GameObject* m_pSpinningDiskUser;
		glm::vec3 m_Velocity;
		glm::vec3 m_Destination;
		float m_MovingSpeed;
		bool m_IsMoving;
		int m_DiskWidth;
		int m_DiskHeight;
		float m_DistinationAcceptanceRadius;

		void AdjustDiskAndDiskUserPosition(std::shared_ptr<TransformComponent>& tranform, std::shared_ptr<TransformComponent>& qbertTransform);
		bool CheckIfDestinationIsReached(std::shared_ptr<TransformComponent>& tranform);
		void StopSpinningDisk();
		
	};


}