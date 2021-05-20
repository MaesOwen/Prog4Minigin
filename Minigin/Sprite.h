#pragma once
#include <SDL_rect.h>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class Sprite final : public dae::Component
	{
	public:
		struct Frame
		{
			int x;
			int y;
			int width;
			int height;
		};
		
		Sprite(int spriteWidth, int spriteHeight);
		void Update() override;
		void Render() const override;
		void SetTexture(const std::string& filename);
		void AddFrame(Frame frame);
		void NextFrame();
		void PrevFrame();
		void SetFrame(int frameNr);

	private:
		std::shared_ptr<dae::Texture2D> m_pTexture;
		std::vector<Frame> m_pFrames;
		int m_CurrentFrame;
		int m_SpriteWidth;
		int m_SpriteHeight;
	};
}

