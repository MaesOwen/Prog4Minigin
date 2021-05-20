#include "MiniginPCH.h"
#include "Platform.h"

#include "GameObject.h"
#include "Qbert.h"
#include "Sprite.h"


dae::Platform::Platform(PlatFormCoords platform, int maxNrOfColorChanges, bool doesJumpingAgainReset)
	:m_PlatformCoords(platform)
	,m_MaxNrOfColorChanges(maxNrOfColorChanges)
	,m_CurrNrOfColorChanges(0)
	,m_DoesJumpingAgainReset(doesJumpingAgainReset)
{
}

void dae::Platform::Update()
{
}

void dae::Platform::Render() const
{
}

void dae::Platform::JumpOff(std::shared_ptr<dae::GameObject>& gameobject)
{
	//m_pGameObjectsOnPlatform.erase(std::find(m_pGameObjectsOnPlatform.begin(), m_pGameObjectsOnPlatform.end(), weakGO));
}

const dae::Platform::PlatFormCoords& dae::Platform::GetPlatFormCoords()
{
	return m_PlatformCoords;
}

std::vector<std::weak_ptr<dae::GameObject>>& dae::Platform::GetGameObjectsOnPlatform()
{
	return m_pGameObjectsOnPlatform;
}

void dae::Platform::JumpOn(std::shared_ptr<dae::GameObject>& gameobject)
{
	m_pGameObjectsOnPlatform.push_back(gameobject);
	
	auto qbert = gameobject->GetComponent<dae::Qbert>();
	if (qbert)
	{
		auto sprite = m_pOwner->GetComponent<dae::Sprite>();
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
