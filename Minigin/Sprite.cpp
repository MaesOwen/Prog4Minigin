#include "MiniginPCH.h"
#include "Sprite.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::Sprite::Sprite(int spriteWidth, int spriteHeight)
	:m_SpriteWidth(spriteWidth)
	,m_SpriteHeight(spriteHeight)
	,m_CurrentFrame(0)
{
}

void dae::Sprite::Update()
{
}

void dae::Sprite::Render() const
{
	if (m_pTexture != nullptr && m_pFrames.size() > 0)
	{
		const auto pos = m_pOwner->GetTransformComponent()->GetPosition();
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
