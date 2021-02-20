#pragma once

#include <deque>

#include "Transform.h"
#include "SceneObject.h"

namespace dae
{
	class Component;
	class Texture2D;
	class TransformComponent;
	class GameObject final: public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;
		void SetPosition(const float x, const float y, const float z);
		std::shared_ptr<TransformComponent> GetTransformComponent() const;
		void AddComponent(std::shared_ptr<Component> pComponent);
		
		template <typename T>
		std::shared_ptr<T> GetComponent()
		{
			for (auto& pComponent: m_pComponents)
			{
				//std::dynamic_pointer_cast<std::shared_ptr<T>>(pComponent)
				if (dynamic_cast<T*>(pComponent.get()))
				{
					return std::dynamic_pointer_cast<T>(pComponent);
				}
			}
			return nullptr;
		};

		

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other);
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		//std::shared_ptr<TransformComponent> m_pTransformComponent; //todo: push components in front, transform always at the back (deque)
		std::deque<std::shared_ptr<Component>> m_pComponents; 
	};
}
