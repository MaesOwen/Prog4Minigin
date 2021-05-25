#include "MiniginPCH.h"
#include "Platform.h"

#include "GameObject.h"
#include "Qbert.h"
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
	auto pos = m_pOwner->GetTransformComponent()->GetPosition();
	//Renderer::GetInstance().DrawRect({int(m_TopSidePos.x),int(m_TopSidePos.y), 5,5 }, 255, 0, 0, 1);
	Renderer::GetInstance().DrawRect({ int(m_TopSidePos.x),int(m_TopSidePos.y), 5,5 }, 0, 255, 0, 1);
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

void dae::Platform::JumpOn(std::shared_ptr<GameObject>& gameobject)
{
	m_pGameObjectsOnPlatform.push_back(gameobject);
	
	auto qbert = gameobject->GetComponent<Qbert>();
	if (qbert)
	{
		auto sprite = m_pOwner->GetComponent<Sprite>();
		if (sprite)
		{
			
			if (m_DoesJumpingAgainReset)
			{
				if (m_CurrNrOfColorChanges + 1 == m_MaxNrOfColorChanges)
				{
					
				}
			}
			else
			{
				if (m_CurrNrOfColorChanges + 1 <= m_MaxNrOfColorChanges)
				{
					m_CurrNrOfColorChanges++;
					sprite->NextFrame();
				}
			}
			sprite->SetFrame(m_CurrNrOfColorChanges);
		}
	}
}
