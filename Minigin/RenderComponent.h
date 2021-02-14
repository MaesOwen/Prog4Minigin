#pragma once
#include "Texture2D.h"

namespace dae
{
	class Transform;
	class RenderComponent final
	{
	public:
		RenderComponent() = default;
		
		void Render(const Transform& transform) const;
		void SetTexture(const std::string& filename);
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		
	};
}