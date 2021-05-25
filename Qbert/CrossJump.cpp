#include "MiniginPCH.h"
#include "CrossJump.h"
#include "TimeMinigin.h"
#include "GameObject.h"
#include "Sprite.h"
#include "TransformComponent.h"

CrossJump::CrossJump()
	:m_IsJumping(false)
	, m_CurrentCoords({ 0,0 })
	, m_Velocity()
	, m_JumpingHeight(100)
	, m_Gravity(0, 9.81f, 0)
{
}

void CrossJump::Update()
{
	if (m_IsJumping)
	{
		auto transform = m_pOwner->GetTransformComponent();
		auto newPos = transform->GetPosition() + m_Velocity * dae::TimeMinigin::GetInstance().GetDeltaTime();
		transform->SetPosition(newPos.x, newPos.y, newPos.z);

		auto platformTopPos = m_PlatformMap.find({ m_CurrentCoords.row, m_CurrentCoords.col })->second->GetTopSidePos();

		if (m_IsGravityActive && transform->GetPosition().y >= platformTopPos.y)
		{
			transform->SetPosition(platformTopPos.x, platformTopPos.y, platformTopPos.z);
			m_IsJumping = false;
			LandOnPlatform();
		}

		CheckGravity(transform->GetPosition().y, platformTopPos.y);
		
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
	if (!m_IsJumping)
	{


		int rowJump = 0;
		int colJump = 0;

		switch (dirCrossJump)
		{
		case DirCrossJump::topLeft:
			m_IsJumpingUpwards = true;
			rowJump = -1;
			colJump = -1;
			break;
		case DirCrossJump::topRight:
			m_IsJumpingUpwards = true;
			rowJump = -1;
			break;
		case DirCrossJump::bottomLeft:
			m_IsJumpingUpwards = false;
			rowJump = 1;
			break;
		case DirCrossJump::bottomRight:
			m_IsJumpingUpwards = false;
			rowJump = 1;
			colJump = 1;
			break;
		}

		ChangeSprite(dirCrossJump);
		
		auto platformIT = m_PlatformMap.find({ m_CurrentCoords.row + rowJump, m_CurrentCoords.col + colJump });

		if (platformIT != m_PlatformMap.end())
		{
			JumpToPos(platformIT->second->GetTopSidePos());

			m_CurrentCoords.row += rowJump;
			m_CurrentCoords.col += colJump;

		}
	}


}

void CrossJump::JumpToPos(const glm::vec3& pos)
{
	glm::vec3 dir = pos - m_PlatformMap.find({ m_CurrentCoords.row, m_CurrentCoords.col })->second->GetTopSidePos();
	float length = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
	dir /= length;
	
	
	
	if (!m_IsJumpingUpwards)
	{
		dir.y *= -1;
		m_Velocity = dir * m_JumpingHeight;
		
	}else
	{
		dir += glm::vec3{0, -1, 0};
		length = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
		dir /= length;
		m_Velocity = dir * (m_JumpingHeight * 1.3f);
	}

	
	
	m_IsJumping = true;
}

void CrossJump::LandOnPlatform()
{
	auto sprite = m_pOwner->GetComponent<dae::Sprite>();
	if (sprite)
		sprite->NextFrame();

	auto platform = m_PlatformMap.find({ m_CurrentCoords.row, m_CurrentCoords.col })->second;
	if(platform)
		platform->JumpOn(m_pOwner);
}

void CrossJump::CheckGravity(float objectPosY, float platformPosY)
{
	if (objectPosY < platformPosY)
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
	auto sprite = m_pOwner->GetComponent<dae::Sprite>();
	if(sprite)
	{
		switch (dirCrossJump)
		{
		case DirCrossJump::topLeft:
			sprite->SetFrame(4);
			break;
		case DirCrossJump::topRight:
			sprite->SetFrame(6);
			break;
		case DirCrossJump::bottomLeft:
			sprite->SetFrame(0);
			break;
		case DirCrossJump::bottomRight:
			sprite->SetFrame(2);
			break;
		}
	}
}
