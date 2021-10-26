#pragma once
#include <functional>
#include <list>

namespace util
{
	template <typename ...Args>
	using Event = std::function<void(Args...)>;

	template <typename ...Args>
	class EventHandler
	{
		std::list<Event<Args...>> events {};
	public:
		EventHandler() = default;
		EventHandler(const EventHandler&) = delete;

		~EventHandler()
		{
			events.clear();
		}

		void operator += (const Event<Args...>& event)
		{
			events.emplace_back(event);
		}

		void operator () (Args... args)
		{
			for (auto itr = events.begin(); itr != events.end(); ++itr)
				(*itr)(args...);
		}
	};
}