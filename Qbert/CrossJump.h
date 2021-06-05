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
	void ResetPos();
	void Fall();
	const dae::Platform::PlatFormCoords& GetCurrentCoords() const;
	dae::Platform::PlatFormCoords ConvertDirectionToCoords(DirCrossJump dirJump) const;
	DirCrossJump ConvertCoordsToDirection(const dae::Platform::PlatFormCoords& coords);

private:
	bool m_IsJumping;
	bool m_IsStuck;
	bool m_IsJumpingUpwards;
	bool m_IsGravityActive;
	dae::Platform::PlatFormCoords m_CurrentCoords;
	std::map<dae::Platform::PlatFormCoords, std::shared_ptr<dae::Platform>> m_PlatformMap;
	glm::vec3 m_Velocity;
	glm::vec3 m_Gravity;
	float m_JumpingHeight;
	bool m_IsOnBottomPlatform;
	bool m_IsJumpingOff;
	float m_ElapsedTimeJumping;
	float m_TimeJumpUntilDeath;

	void JumpToPos(const glm::vec3& pos);
	void LandOnPlatform();
	void CheckGravity(float objectPosY, float platformPosY);
	void ChangeSprite(DirCrossJump dirCrossJump);
	bool CheckIfPlatformsAreComplete();
	bool CheckIfOnBottomPlatform();
	void CheckFallingTime();
	void JumpOffLevelGrid(int row, int col);
	bool CheckIfPlatformIsValid(std::shared_ptr<dae::Platform>& nextPlatform);
};
