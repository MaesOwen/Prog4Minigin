#include "MiniginPCH.h"
#include "Platform.h"


#include "AudioLocator.h"
#include "GameObject.h"
#include "Qbert.h"
#include "QbertSounds.h"
#include "Renderer.h"
#include "Sprite.h"
#include "TransformComponent.h"


dae::Platform::Platform(PlatFormCoords platform, int maxNrOfColorChanges, bool doesJumpingAgainReset)
	:m_PlatformCoords(platform)
	,m_MaxNrOfColorChanges(maxNrOfColorChanges)
	,m_CurrNrOfColorChanges(0)
	,m_DoesJumpingAgainReset(doesJumpingAgainReset)
	,m_AreSidesPosSet(false)
	,m_TopSidePos{}
{
	
}

void dae::Platform::Update()
{
}

void dae::Platform::Render() const
{
	auto owner = GetOwner();
	if(owner)
	{
		auto pos = owner->GetTransformComponent()->GetPosition();
		//Renderer::GetInstance().DrawRect({int(m_TopSidePos.x),int(m_TopSidePos.y), 5,5 }, 255, 0, 0, 1);
		Renderer::GetInstance().DrawRect({ int(m_TopSidePos.x),int(m_TopSidePos.y), 5,5 }, 0, 255, 0, 1);
	}
	
}

void dae::Platform::JumpOff(std::shared_ptr<dae::GameObject>& gameobject)
{
	//m_pGameObjectsOnPlatform.erase(std::find(m_pGameObjectsOnPlatform.begin(), m_pGameObjectsOnPlatform.end(), weakGO));
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

std::vector<std::weak_ptr<dae::GameObject>>& dae::Platform::GetGameObjectsOnPlatform()
{
	return m_pGameObjectsOnPlatform;
}

bool dae::Platform::IsTargetColor() const
{
	return m_CurrNrOfColorChanges == m_MaxNrOfColorChanges;
}

void dae::Platform::ChangePlatformTile(std::shared_ptr<Qbert>& qbert)
{
	qbert->ChangeTile();

	auto gridGO = GetOwner()->GetParent();
	if(auto sharedGridGO = GetOwner()->GetParent().lock())
	{
		std::cout << "there is a parent" << std::endl;
	}
}

void dae::Platform::JumpOn(std::shared_ptr<GameObject>& gameobject)
{
	m_pGameObjectsOnPlatform.push_back(gameobject);
	auto qbertSound = gameobject->GetComponent<QbertSounds>();
	//dae::AudioLocator::GetInstance().GetAudioSystem()->Play(1, 0.1f);
	if (qbertSound)
		qbertSound->PlayQbertSound(QbertSounds::land);
	
	auto qbert = gameobject->GetComponent<Qbert>();
	if (qbert)
	{
		
		auto sprite = GetOwner()->GetComponent<Sprite>();
		if (sprite)
		{
			
			if (m_DoesJumpingAgainReset)
			{
				if (m_CurrNrOfColorChanges + 1 <= m_MaxNrOfColorChanges)
				{
					m_CurrNrOfColorChanges++;

					ChangePlatformTile(qbert);
				}else
				{
					m_CurrNrOfColorChanges = 0;
				}
			}
			else
			{
				if (m_CurrNrOfColorChanges + 1 <= m_MaxNrOfColorChanges)
				{
					m_CurrNrOfColorChanges++;
					
					ChangePlatformTile(qbert);
					
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
