#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject final: public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject(std::shared_ptr<RenderComponent>& pRenderComponent, std::shared_ptr<TextComponent>& pTextComponent, std::shared_ptr<FPSComponent>& pFpsComponent);
		GameObject(std::shared_ptr<RenderComponent>& pRenderComponent);
		GameObject(std::shared_ptr<TextComponent>& pTextComponent);
		GameObject(std::shared_ptr<FPSComponent>& pFpsComponent);
		//TODO: Make all the components derive from a component class ??
		
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		//TODO: Make a container of components?
		std::shared_ptr<RenderComponent> m_pRenderComponent;
		std::shared_ptr<TextComponent> m_pTextComponent;
		std::shared_ptr<FPSComponent> m_pFPSComponent;
	};
}
