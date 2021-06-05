#include "MiniginPCH.h"
#include "Coily.h"



#include "BallAI.h"
#include "CoilyAI.h"
#include "GameObject.h"
#include "QbertSprite.h"
#include "QbertObserver.h"


dae::Coily::Coily(int coilyWidth, int coilyHeight)
	:m_CoilyWidth(coilyWidth)
	, m_CoilyHeight(coilyHeight)
	
{
}

void dae::Coily::Render() const
{
	
}

void dae::Coily::Update()
{
}

void dae::Coily::Die()
{
	for (std::shared_ptr<QbertObserver> pObserver : m_pObservers)
	{
		pObserver->Died(QbertObserver::EnemyThatDied::Coily);
	}
}

void dae::Coily::ChangeTile()
{
}

void dae::Coily::SetOwner(GameObject* pOwner)
{
	m_pOwner = pOwner;

	CheckForSpriteComponent();

	CheckForAIComponents();

	
}

void dae::Coily::CheckForSpriteComponent()
{
	auto sprite = m_pOwner->GetComponent<QbertSprite>();
	
	if (!sprite)
		sprite = std::make_shared<QbertSprite>(m_CoilyWidth, m_CoilyHeight);

	sprite->SetTexture("sprites.png");
	sprite->AddSpritePose(QbertSprite::SpritePose::botLeftJump, sprite->AddFrame({ 112,32, 15, 31 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::botLeftLand, sprite->AddFrame({ 96,32, 15, 31 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::botRightJump, sprite->AddFrame({ 80,32, 15, 31 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::botRightLand, sprite->AddFrame({ 64,32, 15, 31 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::topLeftJump, sprite->AddFrame({ 48,32, 15, 31 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::topLeftLand, sprite->AddFrame({ 32,32, 15, 31 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::topRightJump, sprite->AddFrame({ 16,32, 15, 31 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::topLeftJump, sprite->AddFrame({ 0,32, 15, 31 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::ballJump, sprite->AddFrame({ 80,16,15,15 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::ballLand, sprite->AddFrame({ 64,16,15,15 }));


	sprite->SetSpriteAlignment(Sprite::SpriteAlignment::botMiddle);

	sprite->SetIsBall(true);
	sprite->UseSpritePose(QbertSprite::SpritePose::ballJump);

	m_pOwner->AddComponent(sprite);
}

void dae::Coily::CheckForAIComponents()
{
	auto ballAI = m_pOwner->GetComponent<BallAI>();

	if (!ballAI)
		ballAI = std::make_shared<BallAI>();

	m_pOwner->AddComponent(ballAI);
	
	auto coilyAI = m_pOwner->GetComponent<CoilyAI>();

	if (!coilyAI)
		coilyAI = std::make_shared<CoilyAI>();

	m_pOwner->AddComponent(coilyAI);
}

