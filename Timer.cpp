#include <iostream>
#include "Timer.hpp"

namespace util
{
	Timer::Timer(const char* name) :
		name(name)
	{
		Restart();
	}

	Timer::~Timer()
	{
		Stop();
	}

	void Timer::Restart()
	{
		begin = Clock::now();
		isRunning = true;
	}

	void Timer::Stop()
	{
		TimePoint now = Clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(begin).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch().count();

		auto us = end - start;
		double ms = us / 1000;

		std::cout << name << ": " << us << "us (" << ms << "ms)" << std::endl;

		isRunning = false;
	}
}