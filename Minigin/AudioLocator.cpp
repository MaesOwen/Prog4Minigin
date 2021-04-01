
#include "MiniginPCH.h"
#include "AudioLocator.h"

dae::AudioSystem* dae::AudioLocator::GetAudioSystem()
{
	if (m_pCurrentAudioSystem != nullptr)
	{
		return  m_pCurrentAudioSystem;
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
