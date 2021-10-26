#pragma once
#include <chrono>

namespace util
{
	class Timer
	{
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;
		TimePoint begin;
		const char* name;
		bool isRunning = false;
	public:
		Timer(const char* name = "Timer");
		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;
		~Timer();

		void Stop();
		void Restart();

		inline bool IsRunned() const { return isRunning; }
	};
}