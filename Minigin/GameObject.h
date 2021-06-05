#pragma once

#include <deque>
#include <glm/detail/type_vec.hpp>


#include "SceneObject.h"

namespace dae
{
	class Component;
	class Texture2D;
	class TransformComponent;
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;
		void SetPosition(const float x, const float y, const float z);
		void SetPosition(const glm::vec3& pos);
		std::shared_ptr<TransformComponent> GetTransformComponent() const;
		void AddComponent(const std::shared_ptr<Component>& pComponent);
		void SetTag(const std::string& newTag);
		const std::string& GetTag() const;
		void AddChild(std::shared_ptr<GameObject>& childGO);
		std::vector<std::weak_ptr<GameObject>>& GetChildren();
		GameObject* GetParent();
		const int GetChildCount() const;
		bool GetIsActive() const;
		void SetIsActive(bool isActive);
		
		
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
		
		template <typename T>
		bool RemoveComponent()
		{
			for (auto& pComponent : m_pComponents)
			{
				if (dynamic_cast<T*>(pComponent.get()))
				{
					m_pComponents.erase(std::find(m_pComponents.begin(), m_pComponents.end(), pComponent));
					return true;
				}
			}
			return false;
		}
		

		GameObject();
		virtual ~GameObject() = default;
		GameObject(const GameObject& other);
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::deque<std::shared_ptr<Component>> m_pComponents;
		GameObject* m_pParentGO;
		std::vector<std::weak_ptr<GameObject>> m_pChildrenGOs;
		std::string m_Tag;
		bool m_IsActive;

		void MoveChildrenPosition(float x, float y, float z);
		void AddParent(GameObject* pParentGO);
	};
}
