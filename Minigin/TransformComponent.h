#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "Component.h"

namespace dae
{
	class TransformComponent final : public dae::Component
	{
	public:
		void Update() override;
		void Render() const override;
		void SetPosition(const float x, const float y, const float z);
		const glm::vec3& GetPosition() const { return m_Position; }
		
		TransformComponent() = default;
	private:
		glm::vec3 m_Position;
	};
}

