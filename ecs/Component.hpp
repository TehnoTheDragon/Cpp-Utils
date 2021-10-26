#pragma once
#include "ECS.hpp"

namespace ecs
{
	class Component
	{
	public:
		Entity* entity = nullptr;

	public:
		Component() = default;
		virtual ~Component() {};

		virtual void Spawn() {};
		virtual void Update(double time) {};
		virtual void Destroy() {};
	};
}