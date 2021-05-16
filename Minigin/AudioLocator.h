#pragma once

#include "AudioSystem.h"
#include "Singleton.h"


namespace dae
{
	class AudioLocator final: public Singleton<AudioLocator>
	{
	public:
		AudioSystem* GetAudioSystem();
		void ProvideAudioSystem(AudioSystem* pNewAudioSystem);
		void Destroy();

	private:
		AudioSystem* m_pCurrentAudioSystem;
		DefaultAudioSystem* m_pDefaultAudioSystem;

		
	};

}
