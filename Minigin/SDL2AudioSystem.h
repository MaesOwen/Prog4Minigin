#pragma once
#include "AudioSystem.h"
#include <string>
#include <map>
#include "audio.h"
#include <queue>
#include <thread>
#include <mutex>

namespace dae
{
	struct SoundToPlay
	{
		std::string fileName;
		float volumePercentage;
	};	
	class SDL2AudioSystem: public AudioSystem
	{
	public:
		void Play(int id, float volumePereantage) override;
		void Update() override;
		void ToggleMute() override;
		int Load(const std::string& fileName) override;

		SDL2AudioSystem(bool isMuted);
		virtual ~SDL2AudioSystem();
		SDL2AudioSystem(const SDL2AudioSystem& other) = delete;
		SDL2AudioSystem(SDL2AudioSystem&& other) = delete;
		SDL2AudioSystem& operator=(const SDL2AudioSystem& other) = delete;
		SDL2AudioSystem& operator=(SDL2AudioSystem&& other) = delete;

	private:
		std::map<int, std::string> m_LoadedSounds;
		std::queue<SoundToPlay> m_SoundQueue;
		bool m_IsMuted;
		std::thread m_PlaySoundThread;
		std::mutex m_Mutex;
		std::atomic_bool m_isPlaying;
	};
}
