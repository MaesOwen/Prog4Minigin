#pragma once
namespace dae
{
	class GameObject;
	class Command
	{
	public:

		virtual void execute(GameObject& gameObject) = 0;

		Command() = default;
		virtual ~Command() = default;
		Command(const Command&) = delete;
		Command(Command&&) = delete;
		Command& operator=(const Command&) = delete;
		Command& operator=(Command&&) = delete;

	};
}
