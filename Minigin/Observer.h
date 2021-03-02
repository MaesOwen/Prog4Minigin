#pragma once
namespace dae {
	
	class GameObject;

	enum class Event { PlayerDied };

	class Observer
	{
	public:
		Observer() = default;
		virtual void OnNotify(GameObject& gameOject, Event event) = 0;

		virtual ~Observer() = default;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
	private:

	};

}

