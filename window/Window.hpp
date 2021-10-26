#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "utils/Event.hpp"
#include "utils/Timer.hpp"
#include "utils/math/Vector.hpp"

namespace graphics
{
	struct MetaWindow
	{
		const char* title;
		unsigned int width, height;
	};

	struct WindowEvents
	{
		util::EventHandler<double, double> OnRender;
		util::EventHandler<double> OnUpdate;
		util::EventHandler<double> OnHearbeat;

		// Calls when window is closing
		util::EventHandler<GLFWwindow*> OnClose;

		// Calls when window is resizing
		util::EventHandler<GLFWwindow*, int, int> OnResized;

		// Calls when window is moving
		util::EventHandler<GLFWwindow*, int, int> OnPositionChanged;

		// Calls when file(s) drop into window
		util::EventHandler<GLFWwindow*, int, const char**> OnDropFile;

		// Calls when mouse enter or leave window borders
		util::EventHandler<GLFWwindow*, int> OnEnter;

		// Calls when printing
		util::EventHandler<GLFWwindow*, unsigned int> OnKeyboardChar;

		// Calls when input by keyboard
		util::EventHandler<GLFWwindow*, int, int, int, int> OnKeyboardKey;

		// Calls when mouse button is used
		util::EventHandler<GLFWwindow*, int, int, int> OnMouseButton;

		// Calls when mouse is moving
		util::EventHandler<GLFWwindow*, double, double> OnMouseMove;

		// Calls when mouse wheel is scrolling
		util::EventHandler<GLFWwindow*, double, double> OnWheelScroll;

		// Calls when (OpenGL viewport size is changing) window size changing
		util::EventHandler<GLFWwindow*, int, int> OnFramebufferResized;
	};

	struct WindowInputData
	{
		// Keyboard Keys
		bool* keys = new bool[1024];

		// Mouse Buttons
		bool* buttons = new bool[8];

		// Frames, total of Buttons & Keys
		unsigned int* frames = new unsigned int[1032];

		// Current Frame
		unsigned int currentFrame = 0;

		// Mouse Position
		math::Vector2f MousePosition = math::Vector2f(0, 0);
		
		// Mouse Delta
		math::Vector2f MouseDelta = math::Vector2f(0, 0);

		// Is Mouse Locked
		bool IsMouseLocked = false;
	};

	class Window
	{
	public:
		static MetaWindow meta;
		static WindowEvents events;
		static WindowInputData inputData;
		static GLFWwindow* window;
		static util::Timer* timer;

		double time_current = 0, time_last = 0, time_delta = 0;
	public:
		Window(const char* title, unsigned int width = 940, unsigned int height = 480);
		~Window();

		void Init();
		void Run();

		inline bool IsOpen() const { return !glfwWindowShouldClose(window); }
	public:
		bool IsKeyPressed(unsigned int key)
		{
			return IsKeyDown(key) && inputData.frames[key] == inputData.currentFrame;
		}

		bool IsKeyDown(unsigned int key)
		{
			return inputData.keys[key];
		}

		bool IsButtonPressed(unsigned int button)
		{
			return IsButtonDown(button) && inputData.frames[button] == inputData.currentFrame;
		}

		bool IsButtonDown(unsigned int button)
		{
			return inputData.buttons[button];
		}

	public:
		template <typename T>
		math::Vector2<T> ViewportSize()
		{
			return math::Vector2<T>(meta.width, meta.height);
		}

		template <typename T>
		math::Vector2<T> MousePosition()
		{
			return math::Vector2<T>(inputData.MousePosition);
		}

		template <typename T>
		math::Vector2<T> MouseDelta()
		{
			return math::Vector2<T>(inputData.MouseDelta);
		}

	private:
		void terminate() const;
	};
}