#pragma once

#include <deque>

#include "Transform.h"
#include "SceneObject.h"

namespace dae
{
	class Observer;
	class Component;
	class Texture2D;
	class TransformComponent;
	class GameObject: public SceneObject
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
				if (dynamic_cast<T*>(pComponent.get()))
				{
					return std::dynamic_pointer_cast<T>(pComponent);
				}
			}
			return nullptr;
		};

		void AddObserver(std::shared_ptr<Observer> pObserver);
		

		GameObject();
		virtual ~GameObject() = default;
		GameObject(const GameObject& other);
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	protected:
		std::vector< std::shared_ptr<Observer>> m_pObservers;
	private:
		std::deque<std::shared_ptr<Component>> m_pComponents;
		
	};
}
