#pragma once
#include <map>

#include "Component.h"
#include "Platform.h"

class CrossJump: public dae::Component
{
public:
	enum class DirCrossJump {
		topLeft,
		topRight,
		bottomLeft,
		bottomRight
	};

	CrossJump();
	void Update() override;
	void Render() const override;
	void SetPlatformMap(std::shared_ptr<dae::GameObject>& gridGO);
	void Jump(DirCrossJump dirCrossJump);
	void JumpColRow(int row, int col);
	bool IsOnBottomPlatform() const;

private:
	bool m_IsJumping;
	bool m_IsJumpingUpwards;
	bool m_IsGravityActive;
	dae::Platform::PlatFormCoords m_CurrentCoords;
	std::map<dae::Platform::PlatFormCoords, std::shared_ptr<dae::Platform>> m_PlatformMap;
	glm::vec3 m_Velocity;
	glm::vec3 m_Gravity;
	float m_JumpingHeight;
	bool m_IsOnBottomPlatform;

	void JumpToPos(const glm::vec3& pos);
	void LandOnPlatform();
	void CheckGravity(float objectPosY, float platformPosY);
	void ChangeSprite(DirCrossJump dirCrossJump);
	bool CheckIfPlatformsAreComplete();
	bool CheckIfOnBottomPlatform();
};
