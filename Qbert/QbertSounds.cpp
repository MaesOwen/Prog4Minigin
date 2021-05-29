#include "MiniginPCH.h"
#include "QbertSounds.h"

#include "AudioLocator.h"

void QbertSounds::Update()
{
}

void QbertSounds::Render() const
{
}

void QbertSounds::SetQbertSound(Sounds sound, int id)
{
	m_SoundMap.insert(std::pair<Sounds, int>(sound, id));
}

void QbertSounds::PlayQbertSound(Sounds sound)
{
	auto it = m_SoundMap.find(sound);
	if (it != std::end(m_SoundMap))
		dae::AudioLocator::GetInstance().GetAudioSystem()->Play(it->second, 0.1f);
}
