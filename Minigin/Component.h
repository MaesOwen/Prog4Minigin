#pragma once
#include <memory>
#include <vector>
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void SetOwner(std::shared_ptr<GameObject>& pOwner);
		virtual void SetOwner(GameObject* pOwner);
		//virtual std::shared_ptr<GameObject> GetOwner() const;
		virtual GameObject* GetOwner() const;

		Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	
	protected:
		GameObject* m_pOwner;
	private:
		//std::shared_ptr<GameObject> m_pSharedOwner;
	};

}
