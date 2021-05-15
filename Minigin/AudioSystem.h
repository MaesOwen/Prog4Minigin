#pragma once
namespace dae
{
#include <string>
	class AudioSystem
	{
	public:
		virtual void Update() = 0;
		virtual void Play(int id, float volumePereantage) = 0;
		virtual int Load(const std::string& fileName) = 0;
		virtual void ToggleMute() = 0;

		AudioSystem() = default;
		virtual ~AudioSystem() = default;
		AudioSystem(const AudioSystem& other) = delete;
		AudioSystem(AudioSystem&& other) = delete;
		AudioSystem& operator=(const AudioSystem& other) = delete;
		AudioSystem& operator=(AudioSystem&& other) = delete;
	};
}
