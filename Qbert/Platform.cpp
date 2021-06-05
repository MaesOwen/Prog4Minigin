#include "MiniginPCH.h"
#include "Platform.h"


#include "AudioLocator.h"
#include "Coily.h"
#include "GameObject.h"
#include "QbertComponent.h"
#include "QbertSounds.h"
#include "Renderer.h"
#include "SpinningDisk.h"
#include "Sprite.h"
#include "TransformComponent.h"


dae::Platform::Platform(PlatFormCoords platform, int maxNrOfColorChanges, bool doesJumpingAgainReset)
	:m_PlatformCoords(platform)
	, m_MaxNrOfColorChanges(maxNrOfColorChanges)
	, m_CurrNrOfColorChanges(0)
	, m_DoesJumpingAgainReset(doesJumpingAgainReset)
	, m_AreSidesPosSet(false)
	, m_TopSidePos{}
{

}

void dae::Platform::Update()
{
}

void dae::Platform::Render() const
{
	auto owner = GetOwner();
	if (owner)
	{
		auto pos = owner->GetTransformComponent()->GetPosition();
		//Renderer::GetInstance().DrawRect({int(m_TopSidePos.x),int(m_TopSidePos.y), 5,5 }, 255, 0, 0, 1);
		Renderer::GetInstance().DrawRect({ int(m_TopSidePos.x),int(m_TopSidePos.y), 5,5 }, 0, 255, 0, 1);
	}

}

const dae::Platform::PlatFormCoords& dae::Platform::GetPlatFormCoords()
{
	return m_PlatformCoords;
}

const glm::vec3& dae::Platform::GetTopSidePos()
{
	return m_TopSidePos;
}

void dae::Platform::SetTopSidePos(const float x, const float y, const float z)
{
	m_TopSidePos.x = x;
	m_TopSidePos.y = y;
	m_TopSidePos.z = z;
}



bool dae::Platform::IsTargetColor() const
{
	return m_CurrNrOfColorChanges == m_MaxNrOfColorChanges;
}

void dae::Platform::CheckIfQbertAndEnemiesCollide(GameObject* gameObject)
{

	if (gameObject && m_pCurrentGOOnPlatform)
	{
		auto qbert = gameObject->GetComponent<QbertComponent>();
		if (qbert)
		{
			auto coily = m_pCurrentGOOnPlatform->GetComponent<Coily>();
			if (coily)
				qbert->Die();
		}
		else
		{
			auto coily = gameObject->GetComponent<Coily>();
			if (coily)
			{
				auto qbert = m_pCurrentGOOnPlatform->GetComponent<QbertComponent>();
				if (qbert)
					qbert->Die();
			}
		}
	}



}



void dae::Platform::JumpOn(std::shared_ptr<GameObject>& gameobject)
{
	//land stuff
	CheckIfQbertAndEnemiesCollide(gameobject.get());
	m_pCurrentGOOnPlatform = gameobject;

	auto qbertSound = gameobject->GetComponent<QbertSounds>();
	if (qbertSound)
		qbertSound->PlayQbertSound(QbertSounds::land);


	//check if changing colors
	auto qbert = gameobject->GetComponent<QbertComponent>();
	if (qbert)
	{

		auto sprite = GetOwner()->GetComponent<Sprite>();
		if (sprite)
		{

			if (m_DoesJumpingAgainReset)
			{
				if (m_CurrNrOfColorChanges + 1 <= m_MaxNrOfColorChanges)
				{
					qbert->ChangeTile();
					m_CurrNrOfColorChanges++;
				}
				else
				{
					m_CurrNrOfColorChanges = 0;
				}
			}
			else
			{
				if (m_CurrNrOfColorChanges + 1 <= m_MaxNrOfColorChanges)
				{
					qbert->ChangeTile();
					m_CurrNrOfColorChanges++;
				}
			}
			sprite->SetFrame(m_CurrNrOfColorChanges);
		}


	}













}

void dae::Platform::JumpOn(GameObject* gameObject)
{
	auto sharedGO = std::make_shared<GameObject>(*gameObject);
	JumpOn(sharedGO);
}

void dae::Platform::JumpOff(GameObject* gameObject)
{
	m_pCurrentGOOnPlatform.reset();

}

std::shared_ptr<dae::GameObject> dae::Platform::GetCurrentGOOnPlatform() const
{
	return m_pCurrentGOOnPlatform;
}


