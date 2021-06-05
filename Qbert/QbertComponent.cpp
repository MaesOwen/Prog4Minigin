#include "MiniginPCH.h"
#include "QbertComponent.h"

#include "GameObject.h"
#include "QbertObserver.h"
#include "QbertSprite.h"
#include "Renderer.h"
#include "TransformComponent.h"


void dae::QbertComponent::Update()
{
}

void dae::QbertComponent::Render() const
{
	
}

void dae::QbertComponent::SetOwner(GameObject* pOwner)
{
	m_pOwner = pOwner;

	auto sprite = pOwner->GetComponent<QbertSprite>();

	if (!sprite)
		sprite = std::make_shared<QbertSprite>(m_QbertWidth, m_QbertHeight);

	sprite->SetTexture("sprites.png");
	sprite->AddSpritePose(QbertSprite::SpritePose::botLeftJump, sprite->AddFrame({ 112,0,15,15 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::botLeftLand, sprite->AddFrame({ 96,0,15,15 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::botRightJump, sprite->AddFrame({ 80,0,15,15 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::botRightLand, sprite->AddFrame({ 64,0,15,15 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::topLeftJump, sprite->AddFrame({ 48,0,15,15 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::topLeftLand, sprite->AddFrame({ 32,0,15,15 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::topRightJump, sprite->AddFrame({ 16,0,15,15 }));
	sprite->AddSpritePose(QbertSprite::SpritePose::topLeftJump, sprite->AddFrame({ 0,0,15,15 }));

	sprite->SetSpriteAlignment(Sprite::SpriteAlignment::botMiddle);

	sprite->UseSpritePose(QbertSprite::SpritePose::botLeftLand);

	m_pOwner->AddComponent(sprite);
}

void dae::QbertComponent::Die()
{
	if (m_Lives > 0)
	{
		m_Lives--;
	}
	for (std::shared_ptr<QbertObserver> pObserver: m_pObservers)
	{
		pObserver->Died(QbertObserver::EnemyThatDied::Qbert);
	}
	
}

void dae::QbertComponent::ChangeTile()
{
	for (std::shared_ptr<QbertObserver> pObserver : m_pObservers)
	{
		pObserver->ChangeTile();
	}
}

//void dae::QbertComponent::AddObserver(const std::shared_ptr<QbertObserver>& pObserver)
//{
//	m_pObservers.push_back(pObserver);
//	
//}
//
//void dae::QbertComponent::RemoveObserver(const std::shared_ptr<QbertObserver>& pObserver)
//{
//	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver), m_pObservers.end());
//}

int dae::QbertComponent::GetLives() const
{
	return m_Lives;
}

dae::QbertComponent::QbertComponent(int qbertWidth, int qbertHeight)
	:m_QbertWidth(qbertWidth)
,m_QbertHeight(qbertHeight)
{
}

dae::QbertComponent::QbertComponent(const QbertComponent& other)
{
	std::copy(other.m_pObservers.begin(), other.m_pObservers.end(), std::back_inserter(m_pObservers));
	m_Lives = other.m_Lives;
}
