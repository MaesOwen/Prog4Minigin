
#include "MiniginPCH.h"
#include "AudioLocator.h"


dae::AudioSystem* dae::AudioLocator::GetAudioSystem()
{
	if (m_pCurrentAudioSystem != nullptr)
	{
		return  m_pCurrentAudioSystem;
	}
	if (m_pDefaultAudioSystem == nullptr)
	{
		m_pDefaultAudioSystem = new DefaultAudioSystem();
	}
	return m_pDefaultAudioSystem;
}

void dae::AudioLocator::ProvideAudioSystem(AudioSystem* pNewAudioSystem)
{
	if (pNewAudioSystem != nullptr)
	{
		m_pCurrentAudioSystem = pNewAudioSystem;
	}
}

void dae::AudioLocator::Destroy()
{
	delete m_pCurrentAudioSystem;
	delete m_pDefaultAudioSystem;
}
