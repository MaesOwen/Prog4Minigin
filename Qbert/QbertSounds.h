#pragma once
#include <unordered_map>

#include "Component.h"

class QbertSounds: public dae::Component
{
public:
	enum Sounds
	{
		land,
		die,
		win,
		teleport,
		
	};
	
	void Update() override;
	void Render() const override;

	void SetQbertSound(Sounds sound, int id);
	void PlayQbertSound(Sounds sound);

private:
	std::unordered_map<Sounds, int> m_SoundMap;
};
