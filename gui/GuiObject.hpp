#pragma once
#include <memory>
#include <list>
#include "utils/math/Vector.hpp"

namespace gui
{
	struct GuiBase
	{
		math::Vector3f AbsolutePosition;
		math::Vector2f AbsoluteSize;
		math::Vector3f AbsoluteRotation;
	};

	class GuiObject : public GuiBase
	{
	public:
		std::list<std::unique_ptr<GuiObject>> guiObjects;
		GuiObject* parent;

	public:
		virtual void Update(double) = 0;
		virtual void Render(double, double) = 0;

	public:
		template <typename TGuiObject>
		inline TGuiObject& CreateGuiObject()
		{
			TGuiObject* guiObject(new TGuiObject());
			auto uPtr = std::unique_ptr{ guiObject };
			guiObjects.emplace_back(std::move(uPtr));

			return *guiObject;
		};

	};
}