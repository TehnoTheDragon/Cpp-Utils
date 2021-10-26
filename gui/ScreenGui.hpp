#pragma once
#include <memory>
#include <list>
#include "GuiObject.hpp"
#include "utils/graphics/window/Window.hpp"

namespace gui
{
	class ScreenGui : public GuiObject
	{
	private:
		graphics::Window* window;
	public:
		ScreenGui(graphics::Window* window) :
			window(window)
		{
			this->parent = nullptr;
		}
	public:
		void Update(double);
		void Render(double, double);

		graphics::Window* GetWindow() const { return window; };
	};
}