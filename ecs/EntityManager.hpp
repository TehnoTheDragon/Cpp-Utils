#pragma once
#include "ECS.hpp"

namespace ecs
{
	class EntityManager
	{
	private:
		std::vector<std::unique_ptr<Entity>> entities;

	public:
		inline void Update(double time)
		{
			for (auto& e : entities) e->Update(time);
		}
		
		inline void Refresh()
		{
			entities.erase(std::remove_if(std::begin(entities), std::end(entities),
				[](const std::unique_ptr<Entity>& e)
				{
					return !e->IsActive();
				}
			), std::end(entities));
		}

		inline Entity& AddEntity()
		{
			Entity* e = new Entity();
			std::unique_ptr<Entity> uPtr{ e };
			entities.emplace_back(std::move(uPtr));
			return *e;
		}
	};
}