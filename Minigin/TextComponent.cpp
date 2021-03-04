#include "MiniginPCH.h"
#include "TextComponent.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "Texture2D.h"

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_TextColor);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_pTexture != nullptr) 
	{
		const auto pos = m_pTransform->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetOwner(std::shared_ptr<GameObject> pOwner)
{
	Component::SetOwner(pOwner);
	const auto pos = pOwner->GetTransformComponent()->GetPosition();
	m_pTransform->SetPosition(pos.x, pos.y, pos.z);
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition(float x, float y)
{
	const auto pos = m_pOwner->GetTransformComponent()->GetPosition();
	m_pTransform->SetPosition(pos.x + x, pos.y + y, pos.z + 0.0f);
}

void dae::TextComponent::SetTextColor(UINT8 r, UINT8 g, UINT8 b)
{
	m_TextColor.r = r;
	m_TextColor.g = g;
	m_TextColor.b = b;
}

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(font), m_pTexture(nullptr), m_TextColor({ 255, 255, 255 })
{
	m_pTransform = std::make_shared<TransformComponent>();
}
