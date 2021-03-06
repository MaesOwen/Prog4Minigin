#pragma once
#include <SDL_rect.h>
#include <glm/detail/type_vec.hpp>


#include "Component.h"

namespace dae
{
	class Texture2D;

	class Sprite : public dae::Component
	{
	public:
		enum class SpriteAlignment
		{
			topLeft,
			topMiddle,
			topRight,
			middle,
			botLeft,
			botMiddle,
			botRight,
			
		};
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
		void SetSpriteAlignment(SpriteAlignment spriteAlignment);
		int AddFrame(Frame frame);
		void NextFrame();
		void PrevFrame();
		void SetFrame(int frameNr);
		void ClearFrames();
		void SetTimePerFrame(float timePerFrame);
		void Play();
		void Stop();
		void Reset();
		int GetWidth() const;
		int GetHeight() const;

	protected:
		int m_SpriteWidth;
		int m_SpriteHeight;

		glm::vec3 ChangePosToAlignment(const glm::vec3 pos) const;
	
	private:
		std::shared_ptr<dae::Texture2D> m_pTexture;
		std::vector<Frame> m_pFrames;
		int m_CurrentFrame;
		float m_ElapsedFrameTime;
		float m_FrameTime;
		bool m_IsPlaying;
		SpriteAlignment m_SpriteAlignment;

		
	};
}

