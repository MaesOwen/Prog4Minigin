#pragma once
namespace dae
{
	class GameObject;
	class Command
	{
	public:

		virtual void execute() = 0;

		Command(const std::shared_ptr<GameObject>& pGameObject);
		virtual ~Command() = default;
		Command(const Command&) = delete;
		Command(Command&&) = delete;
		Command& operator=(const Command&) = delete;
		Command& operator=(Command&&) = delete;
	
	protected:
		std::shared_ptr<GameObject> m_pGameObject;

	};
}
