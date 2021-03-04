#pragma once
#include <SDL_pixels.h>

#include "Component.h"
#include "Transform.h"
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;
	class Font;
	class TextComponent final: public Component
	{
	public:
		void Update() override;
		void Render() const override;
		void SetOwner(std::shared_ptr<GameObject> pOwner) override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetTextColor(UINT8 r, UINT8 g, UINT8 b);

		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<TransformComponent> m_pTransform;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTexture;
		SDL_Color m_TextColor;
	};
}
