#pragma once
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void SetOwner(std::shared_ptr<GameObject> pOwner);

		Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	
	protected:
		std::shared_ptr<GameObject> m_pOwner;
	private:
		
	};

}
