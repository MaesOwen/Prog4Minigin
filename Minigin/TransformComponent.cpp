#include "MiniginPCH.h"
#include "TransformComponent.h"

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::Render() const
{
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::TransformComponent::AddToPosition(const float x, const float y, const float z)
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}
