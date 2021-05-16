#include "MiniginPCH.h"
#include "SDL2AudioSystem.h"


#include <audio.h>
#include <SDL.h>

void dae::SDL2AudioSystem::Play(int id, float volumePereantage)
{
	std::cout << "Try to play " << id << ", volume: " << volumePereantage << std::endl;
	std::lock_guard<std::mutex> lock{ m_Mutex };
	m_SoundQueue.push(SoundToPlay{ m_LoadedSounds.find(id)->second , volumePereantage });
	m_isPlaying.store(true);
}



int dae::SDL2AudioSystem::Load(const std::string& fileName)
{
	int newId = int(m_LoadedSounds.size());
	
	m_LoadedSounds.insert(std::pair<int, std::string>(newId, fileName));
	
	
	return newId;
}

void dae::SDL2AudioSystem::ToggleMute()
{
	m_IsMuted = !m_IsMuted;
}

void dae::SDL2AudioSystem::Update()
{
	SoundToPlay soundToPlay{};
	while (m_isPlaying.load())
	{
		while (!m_SoundQueue.empty())
		{
			std::unique_lock<std::mutex> lock{ m_Mutex };
			soundToPlay = m_SoundQueue.front();
			m_SoundQueue.pop();
			if (!m_IsMuted)
			{
				playSound(soundToPlay.fileName.c_str(), int(SDL_MIX_MAXVOLUME * soundToPlay.volumePercentage)); //linked error from initAudio
				std::cout << "Play sound with path: " << soundToPlay.fileName << " at volume " << SDL_MIX_MAXVOLUME * soundToPlay.volumePercentage << std::endl;
			}
		}
	}
	
}

dae::SDL2AudioSystem::SDL2AudioSystem(bool isMuted)
	:m_IsMuted(isMuted)
{
	m_isPlaying.store(true);
	m_PlaySoundThread = std::thread([this]() { this->Update(); });
}

dae::SDL2AudioSystem::~SDL2AudioSystem()
{
	m_isPlaying.store(false);
	m_PlaySoundThread.join();
}

