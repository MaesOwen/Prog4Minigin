#include "MiniginPCH.h"
#include "QbertSprite.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"


dae::QbertSprite::QbertSprite(int spriteWidth, int spriteHeight)
	:Sprite(spriteWidth, spriteHeight)
	,m_BaseSpriteHeight(spriteHeight)
	,m_IsBall(false)
{
	
}



void dae::QbertSprite::UseSpritePose(SpritePose spritePose)
{
	auto spritePoseIT = m_SpritePosMap.find(spritePose);
	if(spritePoseIT != m_SpritePosMap.end())
	{
		SetFrame(spritePoseIT->second);
	}
		
}

void dae::QbertSprite::AddSpritePose(SpritePose spritePose, int frameNr)
{
	m_SpritePosMap.insert({ spritePose, frameNr });
}

bool dae::QbertSprite::GetIsBall() const
{
	return m_IsBall;
}

void dae::QbertSprite::SetIsBall(bool isBall)
{
	if(isBall)
	{
		m_SpriteHeight = m_BaseSpriteHeight / 2;
	}else
	{
		m_SpriteHeight = m_BaseSpriteHeight;
	}
	m_IsBall = isBall;
}
