#pragma once
#include "ECS.hpp"

namespace ecs
{
	class Entity
	{
	private:
		bool Active = true;
		std::vector<std::unique_ptr<Component>> components;

		ComponentArray componentArray;
		ComponentBitSet componentBitSet;
	public:
		inline void Update(double time)
		{
			if (Active)
			{
				for (auto& c : components) c->Update(time);
			}
		};

		inline void Destroy()
		{
			Active = false;
			for (auto& c : components) c->Destroy();
		}

		inline bool IsActive() const { return Active; };

	public:
		template <typename TComponent>
		inline bool HasComponent() const
		{
			return componentBitSet[GetComponentID<TComponent>()];
		}

		template <typename TComponent, typename ...TArgs>
		inline TComponent& AddComponent(TArgs&&... args)
		{
			TComponent* component(new TComponent(std::forward<TArgs>(args)...));
			component->entity = this;
			std::unique_ptr<Component> uPtr{ component };
			components.emplace_back(std::move(uPtr));

			componentArray[GetComponentID<TComponent>()] = component;
			componentBitSet[GetComponentID<TComponent>()] = true;

			component->Spawn();
			return *component;
		}

		template <typename TComponent>
		inline TComponent& GetComponent() const
		{
			auto uPtr(componentArray[GetComponentID<TComponent>()]);
			return *static_cast<TComponent*>(uPtr);
		}

	public:
		Entity() = default;
		virtual ~Entity() {};
	};
}