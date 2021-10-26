#include "ScreenGui.hpp"

namespace gui
{
	void ScreenGui::Update(double t)
	{
		for (auto& g : guiObjects) g->Update(t);
	}

	void ScreenGui::Render(double t, double dt)
	{
		for (auto& g : guiObjects) g->Render(t, dt);
	}
}