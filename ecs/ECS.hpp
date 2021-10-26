#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include "utils/Event.hpp"

namespace ecs
{
	class Component;
	class Entity;

	constexpr std::size_t ECS_MAX_ENTITY = 1000;

	typedef std::size_t ComponentID;
	typedef std::bitset<ECS_MAX_ENTITY> ComponentBitSet;
	typedef std::array<Component*, ECS_MAX_ENTITY> ComponentArray;

	inline ComponentID GetComponentID()
	{
		static ComponentID lastId = 0;
		return lastId++;
	}

	template <typename T>
	inline ComponentID GetComponentID() noexcept
	{
		static ComponentID typeID = GetComponentID();
		return typeID;
	}
}

#include "Component.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"