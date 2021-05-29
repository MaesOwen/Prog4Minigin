#include "MiniginPCH.h"
#include "Sprite.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimeMinigin.h"

dae::Sprite::Sprite(int spriteWidth, int spriteHeight)
	:m_SpriteWidth(spriteWidth)
	,m_SpriteHeight(spriteHeight)
	,m_CurrentFrame(0)
	,m_ElapsedFrameTime(0)
	,m_FrameTime(1.f/4)
	,m_IsPlaying(false)
	,m_SpriteAlignment(SpriteAlignment::topLeft)
{
}

void dae::Sprite::Update()
{
	if(m_IsPlaying)
	{
		m_ElapsedFrameTime += TimeMinigin::GetInstance().GetDeltaTime();
		if (m_ElapsedFrameTime >= m_FrameTime)
		{
			m_ElapsedFrameTime -= m_FrameTime;
			NextFrame();
		}
	}
}

void dae::Sprite::Render() const
{
	auto owner = GetOwner();
	if (m_pTexture != nullptr && m_pFrames.size() > 0 && owner)
	{
		const auto oldpos = owner->GetTransformComponent()->GetPosition();
		const auto pos = ChangePosToAlignment(oldpos);
		Renderer::GetInstance().RenderTexture(
			*m_pTexture,
			SDL_Rect{ m_pFrames[m_CurrentFrame].x, m_pFrames[m_CurrentFrame].y, m_pFrames[m_CurrentFrame].width, m_pFrames[m_CurrentFrame].height},
			SDL_Rect{int(pos.x), int(pos.y), m_SpriteHeight, m_SpriteHeight});
	}
}

void dae::Sprite::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::Sprite::SetSpriteAlignment(SpriteAlignment spriteAlignment)
{
	m_SpriteAlignment = spriteAlignment;
}

void dae::Sprite::AddFrame(Frame frame)
{
	m_pFrames.push_back(frame);
}

void dae::Sprite::NextFrame()
{
	if(m_CurrentFrame + 1 < int(m_pFrames.size()))
	{
		m_CurrentFrame++;
	}else
	{
		m_CurrentFrame = 0;
	}
}

void dae::Sprite::PrevFrame()
{
	if(m_CurrentFrame - 1 >= 0)
	{
		m_CurrentFrame--;
	}else
	{
		m_CurrentFrame = int(m_pFrames.size() - 1);
	}
}

void dae::Sprite::SetFrame(int frameNr)
{
	if (0 <= frameNr && frameNr < int(m_pFrames.size()))
		m_CurrentFrame = frameNr;
}

void dae::Sprite::SetTimePerFrame(float timePerFrame)
{
	m_FrameTime = timePerFrame;
}

void dae::Sprite::Play()
{
	m_IsPlaying = true;
}

void dae::Sprite::Stop()
{
	m_IsPlaying = false;
}

void dae::Sprite::Reset()
{
	m_CurrentFrame = 0;
}

int dae::Sprite::GetWidth() const
{
	return m_SpriteWidth;
}

int dae::Sprite::GetHeight() const
{
	return m_SpriteHeight;
}

 glm::vec3 dae::Sprite::ChangePosToAlignment(const glm::vec3 pos) const 
{
	glm::vec3 newPos;
	newPos.x = pos.x;
	newPos.y = pos.y;
	switch (m_SpriteAlignment)
	{
	case SpriteAlignment::topLeft:
		break;
	case SpriteAlignment::topRight:
		newPos.x -= m_SpriteWidth;
		break;
	case SpriteAlignment::topMiddle:
		newPos.x -= m_SpriteWidth / 2;
		break;
	case SpriteAlignment::middle:
		newPos.x -= m_SpriteWidth / 2;
		newPos.y -= m_SpriteHeight / 2;
		break;
	case SpriteAlignment::botLeft:
		newPos.y -= m_SpriteHeight;
		break;
	case SpriteAlignment::botMiddle:
		newPos.x -= m_SpriteWidth / 2;
		newPos.y -= m_SpriteHeight;
		break;
	case SpriteAlignment::botRight:
		newPos.x -= m_SpriteWidth;
		newPos.y -= m_SpriteHeight;
		break;
	}
	return newPos;
}
