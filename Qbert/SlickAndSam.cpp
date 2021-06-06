#include "MiniginPCH.h"
#include "SlickAndSam.h"

#include "BallAI.h"
#include "GameObject.h"
#include "QbertSprite.h"
#include "QbertObserver.h"

dae::SlickAndSam::SlickAndSam(int slickWidth, int slickHeight, bool isSlick)
	:m_SlickAndSamWidth(slickWidth)
	, m_SlickAndSamHeight(slickHeight)
	, m_IsSlick(isSlick)
{
}

void dae::SlickAndSam::Update()
{
}

void dae::SlickAndSam::Render() const
{
}

void dae::SlickAndSam::SetOwner(dae::GameObject* pOwner)
{
	m_pOwner = pOwner;

	CheckForSpriteComponent();
}

void dae::SlickAndSam::Die()
{
	for (std::shared_ptr<QbertObserver> pObserver : m_pObservers)
	{
		if(m_IsSlick)
		{
			pObserver->Died(QbertObserver::EnemyThatDied::Slick);
		}else
		{
			pObserver->Died(QbertObserver::EnemyThatDied::Sam);
		}
		
	}
}

void dae::SlickAndSam::FallOff()
{
	
}

void dae::SlickAndSam::ChangeTile()
{
}

void dae::SlickAndSam::CheckForSpriteComponent()
{
	auto sprite = m_pOwner->GetComponent<dae::QbertSprite>();

	if (!sprite)
		sprite = std::make_shared<dae::QbertSprite>(m_SlickAndSamWidth, m_SlickAndSamHeight);

	sprite->SetTexture("sprites.png");
	if(m_IsSlick)
	{
		sprite->AddSpritePose(QbertSprite::SpritePose::botLeftJump, sprite->AddFrame({ 16,128, 15, 15 }));
		sprite->AddSpritePose(QbertSprite::SpritePose::botLeftLand, sprite->AddFrame({ 0,128, 15, 15 }));
		sprite->AddSpritePose(QbertSprite::SpritePose::botRightJump, sprite->AddFrame({ 80,128, 15, 15 }));
		sprite->AddSpritePose(QbertSprite::SpritePose::botRightLand, sprite->AddFrame({ 64,128, 15, 15 }));
		
	}else
	{
		sprite->AddSpritePose(QbertSprite::SpritePose::botLeftJump, sprite->AddFrame({ 16,144, 15, 15 }));
		sprite->AddSpritePose(QbertSprite::SpritePose::botLeftLand, sprite->AddFrame({ 0,144, 15, 15 }));
		sprite->AddSpritePose(QbertSprite::SpritePose::botRightJump, sprite->AddFrame({ 80,144, 15, 15 }));
		sprite->AddSpritePose(QbertSprite::SpritePose::botRightLand, sprite->AddFrame({ 64,144, 15, 15 }));
		
	}
	


	sprite->SetSpriteAlignment(Sprite::SpriteAlignment::botMiddle);

	sprite->UseSpritePose(QbertSprite::SpritePose::botLeftLand);


	m_pOwner->AddComponent(sprite);
}