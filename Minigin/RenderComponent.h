#pragma once
#include "Component.h"
#include "Texture2D.h"

namespace dae
{
	class Transform;
	class RenderComponent final: public Component
	{
	public:
		RenderComponent() = default;
		void Update() override;
		void Render() const override;
		void SetTexture(const std::string& filename);
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		
	};
}