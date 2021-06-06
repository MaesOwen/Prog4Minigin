#include "MiniginPCH.h"
#include "CrossJump.h"

#include "AudioLocator.h"
#include "Coily.h"
#include "TimeMinigin.h"
#include "GameObject.h"
#include "QbertComponent.h"
#include "QbertSprite.h"
#include "SlickAndSam.h"
#include "SpinningDisk.h"
#include "TransformComponent.h"

CrossJump::CrossJump()
	:m_IsJumping(false)
	, m_CurrentCoords({ 0,0 })
	, m_Velocity()
	, m_JumpingHeight(100)
	, m_Gravity(0, 9.81f, 0)
	, m_IsOnBottomPlatform(false)
	, m_IsJumpingOff(false)
	,m_ElapsedTimeJumping(0)
	,m_TimeJumpUntilDeath(1)
	,m_IsStuck()
{
	Fall();
}

void CrossJump::Update()
{
	if (m_IsJumping)
	{
		m_IsStuck = false;
		
		auto transform = GetOwner()->GetTransformComponent();
		auto newPos = transform->GetPosition() + m_Velocity * dae::TimeMinigin::GetInstance().GetDeltaTime();
		transform->SetPosition(newPos.x, newPos.y, newPos.z);

		auto platformTopPos = m_PlatformMap.find({ m_CurrentCoords.row, m_CurrentCoords.col })->second->GetTopSidePos();

		if (m_IsGravityActive && transform->GetPosition().y >= platformTopPos.y && !m_IsJumpingOff)
		{
			transform->SetPosition(platformTopPos.x, platformTopPos.y, platformTopPos.z);
			m_IsJumping = false;
			LandOnPlatform();
		}

		CheckGravity(transform->GetPosition().y, platformTopPos.y);
		CheckFallingTime();
	}
}

void CrossJump::Render() const
{
}

void CrossJump::SetPlatformMap(std::shared_ptr<dae::GameObject>& gridGO)
{
	m_PlatformMap.clear();

	auto weakChildrenGO = gridGO->GetChildren();

	if (weakChildrenGO.size() > 0)
	{
		for (std::weak_ptr<dae::GameObject> weakChildGO : weakChildrenGO)
		{
			if (auto sharedChildGO = weakChildGO.lock())
			{
				auto platform = sharedChildGO->GetComponent<dae::Platform>();
				if (platform)
					m_PlatformMap.insert(std::pair<dae::Platform::PlatFormCoords, std::shared_ptr<dae::Platform>>(platform->GetPlatFormCoords(), platform));
			}
		}
	}

}

void CrossJump::Jump(DirCrossJump dirCrossJump)
{
	if (!m_IsJumping && !m_IsStuck)
	{
		auto currentPlatform = m_PlatformMap.find({ m_CurrentCoords.row, m_CurrentCoords.col })->second;
		if (currentPlatform)
			currentPlatform->JumpOff(GetOwner());

		auto const jumpCoords = ConvertDirectionToCoords(dirCrossJump);

		m_IsJumpingUpwards = jumpCoords.row < 0;

		ChangeSprite(dirCrossJump);

		
		dae::Platform::PlatFormCoords newCoords{ m_CurrentCoords.row + jumpCoords.row , m_CurrentCoords.col + jumpCoords.col };
		auto nextPlatformIT = m_PlatformMap.find(newCoords);

		if (nextPlatformIT != m_PlatformMap.end())
		{
			//todo: check if not other player on platform
			if(CheckIfPlatformIsValid(nextPlatformIT->second))
			{
				JumpToPos(nextPlatformIT->second->GetTopSidePos());

				m_CurrentCoords.row += jumpCoords.row;
				m_CurrentCoords.col += jumpCoords.col;
			}
			
		}
		else
		{
			JumpOffLevelGrid(jumpCoords.row, jumpCoords.col);
			
		}
	}


}

void CrossJump::JumpColRow(int row, int col)
{
	Jump(ConvertCoordsToDirection({ row,col }));
}

bool CrossJump::IsOnBottomPlatform() const
{
	return m_IsOnBottomPlatform;
}

void CrossJump::ResetPos()
{
	m_IsJumping = false;
	m_IsJumpingOff = false;
	//todo: set to spawncoords
	m_CurrentCoords.col = 0;
	m_CurrentCoords.row = 0;
	if (m_pOwner)
	{
		auto pos = m_PlatformMap.at({ 0,0 })->GetTopSidePos();
		m_pOwner->GetTransformComponent()->SetPosition(pos.x, pos.y, pos.z);
	}
	

}

void CrossJump::Fall()
{
	//todo: set to respawn row and coll
	m_CurrentCoords.row = 0;
	m_CurrentCoords.col = 0;
	m_Velocity.x = 0;
	m_Velocity.y = 0;
	m_IsJumping = true;
}

const dae::Platform::PlatFormCoords& CrossJump::GetCurrentCoords() const
{
	return m_CurrentCoords;
}

dae::Platform::PlatFormCoords CrossJump::ConvertDirectionToCoords(DirCrossJump dirJump) const
{
	dae::Platform::PlatFormCoords jumpCoords{};
	
	switch (dirJump)
	{
	case DirCrossJump::topLeft:
		jumpCoords.row = -1;
		jumpCoords.col = -1;
		break;
	case DirCrossJump::topRight:
		jumpCoords.row = -1;
		break;
	case DirCrossJump::bottomLeft:
		jumpCoords.row = 1;
		break;
	case DirCrossJump::bottomRight:
		jumpCoords.row = 1;
		jumpCoords.col = 1;
		break;
	}

	return jumpCoords;
}

CrossJump::DirCrossJump CrossJump::ConvertCoordsToDirection(const dae::Platform::PlatFormCoords& coords)
{
	if (coords.row > 0)
	{
		if (coords.col > 0)
		{
			return DirCrossJump::bottomRight;
		}
		return DirCrossJump::bottomLeft;
	}else
	{
		if (coords.col < 0)
		{
			return DirCrossJump::topLeft;
		}
		return DirCrossJump::topRight;
	}
}

void CrossJump::JumpToPos(const glm::vec3& pos)
{
	glm::vec3 dir = pos - m_PlatformMap.find({ m_CurrentCoords.row, m_CurrentCoords.col })->second->GetTopSidePos();
	float length = float(sqrt(pow(dir.x, 2) + pow(dir.y, 2)));
	dir /= length;



	if (!m_IsJumpingUpwards)
	{
		dir.y *= -1;
		m_Velocity = dir * m_JumpingHeight;

	}
	else
	{
		float jumpUpMultiplier = 1.5f;
		glm::vec3 upwardsVector{ 0, -1, 0 };
		dir += upwardsVector;
		length = float(sqrt(pow(dir.x, 2) + pow(dir.y, 2)));
		dir /= length;
		m_Velocity = dir * (m_JumpingHeight * jumpUpMultiplier);
	}



	m_IsJumping = true;
}

void CrossJump::LandOnPlatform()
{
	auto owner = GetOwner();
	if (owner)
	{
		auto sprite = owner->GetComponent<dae::Sprite>();
		if (sprite)
			sprite->NextFrame();

		auto platform = m_PlatformMap.find({ m_CurrentCoords.row, m_CurrentCoords.col })->second;
		if (platform)
		{
			platform->JumpOn(owner);

			auto spinningDisk = platform->GetOwner()->GetComponent<dae::SpinningDisk>();
			if (spinningDisk)
			{
				auto platform = m_PlatformMap.find({ 0, 0 })->second;
				auto platformHeight = platform->GetOwner()->GetComponent<dae::Sprite>()->GetHeight();
				auto destinationPos = platform->GetTopSidePos();

				destinationPos.y -= platformHeight;
				spinningDisk->MoveQbertToPos(destinationPos, owner);
			}
		}

		

	}

	auto qbert = owner->GetComponent<dae::QbertComponent>();
	if (qbert)
	{
		if (CheckIfPlatformsAreComplete())
		{
			std::cout << "Level completed" << std::endl;
		}
	}

	m_IsOnBottomPlatform = CheckIfOnBottomPlatform();


	//todo: delete
	/*for (auto pair : m_PlatformMap)
	{
		auto spindisk = pair.second->GetOwner()->GetComponent<dae::SpinningDisk>();
		if (spindisk)
			std::cout << "Platform (" << pair.first.row << ", " << pair.first.col << "): Spinning Disk" << std::endl;
		
		auto go = pair.second->GetCurrentGOOnPlatform();
		if (go != nullptr)
		{
			
			auto q = go->GetComponent<dae::QbertComponent>();
			if (q)
				std::cout << "Platform (" << pair.first.row << ", " << pair.first.col << "): Qbert" << std::endl;

			auto c = go->GetComponent<dae::Coily>();
			if (c)
				std::cout << "Platform (" << pair.first.row << ", " << pair.first.col << "): Coily" << std::endl;
		}

	}*/

}

void CrossJump::CheckGravity(float objectPosY, float platformPosY)
{
	if (objectPosY < platformPosY || m_IsJumpingOff)
	{
		m_IsGravityActive = true;
		m_Velocity.y += m_Gravity.y;
	}
	else
	{
		m_IsGravityActive = false;
	}


}

void CrossJump::ChangeSprite(DirCrossJump dirCrossJump)
{
	auto sprite = GetOwner()->GetComponent<dae::QbertSprite>();
	if (sprite)
	{
		if (!sprite->GetIsBall())
		{
			switch (dirCrossJump)
			{
			case DirCrossJump::topLeft:
				sprite->UseSpritePose(dae::QbertSprite::SpritePose::topLeftJump);
				break;
			case DirCrossJump::topRight:
				sprite->UseSpritePose(dae::QbertSprite::SpritePose::topRightJump);
				break;
			case DirCrossJump::bottomLeft:
				sprite->UseSpritePose(dae::QbertSprite::SpritePose::botLeftJump);
				break;
			case DirCrossJump::bottomRight:
				sprite->UseSpritePose(dae::QbertSprite::SpritePose::botRightJump);
				break;
			}
		}
		else
		{
			sprite->UseSpritePose(dae::QbertSprite::SpritePose::ballJump);
		}

	}
}

bool CrossJump::CheckIfPlatformsAreComplete()
{
	for (auto platformIT : m_PlatformMap)
	{
		if (!platformIT.second->IsTargetColor())
		{
			return false;
		}
	}
	return true;
}

bool CrossJump::CheckIfOnBottomPlatform()
{
	auto it = m_PlatformMap.find({ m_CurrentCoords.row + 1, 0 });
	if (it == std::end(m_PlatformMap))
	{
		return true;
	}
	return false;
}

void CrossJump::CheckFallingTime()
{
	if(m_IsJumpingOff)
	{
		m_ElapsedTimeJumping += dae::TimeMinigin::GetInstance().GetDeltaTime();
		if (m_ElapsedTimeJumping > m_TimeJumpUntilDeath)
		{
			m_ElapsedTimeJumping = 0;
			//todo: die component
			if (auto qbert = m_pOwner->GetComponent<dae::QbertComponent>())
			{
				qbert->Die();
			}
			else if (auto coily = m_pOwner->GetComponent<dae::Coily>())
			{
				coily->Die();
			}else if(auto slickAndSam = m_pOwner->GetComponent<dae::SlickAndSam>())
			{
				slickAndSam->Die();
			}
			
			ResetPos();
		}
	}
}

void CrossJump::JumpOffLevelGrid(int row, int col)
{
	std::cout << "No path found" << std::endl;
	auto pos = m_pOwner->GetTransformComponent()->GetPosition();
	pos.x += float(col);
	pos.y += float(row);
	m_IsJumpingOff = true;
	m_IsJumpingUpwards = false;
	JumpToPos(pos);
}

bool CrossJump::CheckIfPlatformIsValid(std::shared_ptr<dae::Platform>& nextPlatform)
{
	auto SpinnerDisk = nextPlatform->GetOwner()->GetComponent<dae::SpinningDisk>();
	if (SpinnerDisk)
	{
		auto qbert = m_pOwner->GetComponent<dae::QbertComponent>();
		if(qbert)
		{
			m_IsStuck = true;
			return true;
		}

		auto coily = m_pOwner->GetComponent<dae::Coily>();
		if(coily)
		{
			auto coords = nextPlatform->GetPlatFormCoords();
			JumpOffLevelGrid(coords.row, coords.col);
		}
		
		return false;

		
	}
		
	return true;
}
