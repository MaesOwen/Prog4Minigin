#include "MiniginPCH.h"
#include "SpinningDisk.h"

#include "QbertSprite.h"
#include "GameObject.h"
#include "TimeMinigin.h"
#include "TransformComponent.h"
#include "CrossJump.h"

dae::SpinningDisk::SpinningDisk(int diskWidth, int diskHeight)
	:m_DiskWidth(diskWidth)
	, m_DiskHeight(diskHeight)
	, m_Velocity()
	, m_Destination()
	, m_MovingSpeed(100)
	, m_IsMoving()
	,m_DistinationAcceptanceRadius(5)
{
}

void dae::SpinningDisk::Update()
{
	if(m_IsMoving)
	{
		auto transform = m_pOwner->GetTransformComponent();
		auto transformQbert = m_pSpinningDiskUser->GetTransformComponent();
		
		AdjustDiskAndDiskUserPosition(transform, transformQbert);

		if(CheckIfDestinationIsReached(transform))
		{
			StopSpinningDisk();
		}
	}
}

void dae::SpinningDisk::Render() const
{
}

void dae::SpinningDisk::SetOwner(GameObject* pOwner)
{
	m_pOwner = pOwner;

	auto sprite = m_pOwner->GetComponent<dae::QbertSprite>();

	if (!sprite)
		sprite = std::make_shared<QbertSprite>(m_DiskWidth, m_DiskHeight);

	sprite->SetTexture("sprites.png");
	sprite->AddFrame({ 64,352,15,15 });
	sprite->AddFrame({ 48,352,15,15 });
	sprite->AddFrame({ 32,352,15,15 });
	sprite->AddFrame({ 16,352,15,15 });
	sprite->AddFrame({ 0,352,15,15 });


	sprite->Play();
	sprite->SetSpriteAlignment(Sprite::SpriteAlignment::botMiddle);



	m_pOwner->AddComponent(sprite);
}

void dae::SpinningDisk::MoveQbertToPos(const glm::vec3& newPos, GameObject* qbertGO)
{
	m_Destination = newPos;
	m_pSpinningDiskUser = qbertGO;
	
	auto pos = m_pOwner->GetTransformComponent()->GetPosition();
	glm::vec3 dir = newPos - pos;
	float length = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
	dir /= length;

	m_Velocity = dir * m_MovingSpeed;
	m_IsMoving = true;
}

void dae::SpinningDisk::AdjustDiskAndDiskUserPosition(std::shared_ptr<TransformComponent>& transform, std::shared_ptr<TransformComponent>& qbertTransform)
{
	auto pos = transform->GetPosition();
	auto qbertPos = qbertTransform->GetPosition();

	float deltaTime = dae::TimeMinigin::GetInstance().GetDeltaTime();

	pos += m_Velocity * deltaTime;
	qbertPos += m_Velocity * deltaTime;

	transform->SetPosition(pos.x, pos.y, pos.z);
	qbertTransform->SetPosition(qbertPos.x, qbertPos.y, qbertPos.z);
}

bool dae::SpinningDisk::CheckIfDestinationIsReached(std::shared_ptr<TransformComponent>& tranform)
{
	auto diskPos = tranform->GetPosition();
	auto vec = m_Destination - diskPos;
	float magnitude = pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2);
	
	return magnitude <= m_DistinationAcceptanceRadius * m_DistinationAcceptanceRadius;
}

void dae::SpinningDisk::StopSpinningDisk()
{
	m_IsMoving = false;
	auto jump = m_pSpinningDiskUser->GetComponent<CrossJump>();
	if (jump)
		jump->Fall();
	
	m_pOwner->SetIsActive(false);
}
