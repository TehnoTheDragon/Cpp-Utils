#include "Window.hpp"

namespace graphics
{
	MetaWindow Window::meta;
	WindowInputData Window::inputData;
	WindowEvents Window::events;
	GLFWwindow* Window::window;
	util::Timer* Window::timer = new util::Timer("Window Process");

	Window::Window(const char* title, unsigned int width, unsigned int height)
	{
		meta.title = title;
		meta.width = width;
		meta.height = height;

		memset(inputData.keys, false, 1024);
		memset(inputData.buttons, false, 8);
		memset(inputData.frames, 0, 1032);
	}

	Window::~Window()
	{
		delete[] inputData.keys;
		delete[] inputData.buttons;
		delete[] inputData.frames;

		terminate();
	}

	void Window::Init()
	{
		if (glfwInit() != GLFW_TRUE)
			throw std::exception("Catched error while glfw initing!");

		window = glfwCreateWindow(meta.width, meta.height, meta.title, 0, 0);
		if (!window)
			throw std::exception("Catched error while creating window!");

#pragma region GLFW Events

		// Size
		glfwSetWindowSizeCallback(window,
			[](GLFWwindow* window, int w, int h)
			{
				events.OnResized(window, w, h);
				meta.width = w;
				meta.height = h;
			});

		// Position
		glfwSetWindowPosCallback(window,
			[](GLFWwindow* window, int w, int h)
			{
				events.OnPositionChanged(window, w, h);
			});

		// Drop File
		glfwSetDropCallback(window,
			[](GLFWwindow* window, int count, const char** paths)
			{
				events.OnDropFile(window, count, paths);
			});

		// Cursor Enter
		glfwSetCursorEnterCallback(window,
			[](GLFWwindow* window, int entered)
			{
				events.OnEnter(window, entered);
			});

		// Char
		glfwSetCharCallback(window,
			[](GLFWwindow* window, unsigned int character)
			{
				events.OnKeyboardChar(window, character);
			});

		// Keyboard Input
		glfwSetKeyCallback(window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods) 
			{
				events.OnKeyboardKey(window, key, scancode, action, mods);

				if (action == GLFW_PRESS)
				{
					inputData.keys[key] = true;
					inputData.frames[key] = inputData.currentFrame;
				}
				else if (action == GLFW_RELEASE)
				{
					inputData.keys[key] = false;
					inputData.frames[key] = inputData.currentFrame;
				}
			});

		// Mouse Button Input
		glfwSetMouseButtonCallback(window,
			[](GLFWwindow* window, int button, int action, int mods)
			{
				events.OnMouseButton(window, button, action, mods);

				if (action == GLFW_PRESS)
				{
					inputData.buttons[button] = true;
					inputData.frames[button] = inputData.currentFrame;
				}
				else if (action == GLFW_RELEASE)
				{
					inputData.buttons[button] = false;
					inputData.frames[button] = inputData.currentFrame;
				}
			});

		// Mouse Move
		glfwSetCursorPosCallback(window,
			[](GLFWwindow* window, double x, double y)
			{
				events.OnMouseMove(window, x, y);

				auto NewMousePosition = math::Vector2f(x, y);

				if (inputData.IsMouseLocked)
				{
					inputData.MouseDelta = NewMousePosition - inputData.MousePosition;
				}
				inputData.MousePosition = NewMousePosition;
			});

		// Mouse Scroll
		glfwSetScrollCallback(window,
			[](GLFWwindow* window, double x, double y)
			{
				events.OnWheelScroll(window, x, y);
			});

		// Framebuffer Resized
		glfwSetFramebufferSizeCallback(window,
			[](GLFWwindow* window, int w, int h)
			{
				events.OnFramebufferResized(window, w, h);
			});

		// Close
		glfwSetWindowCloseCallback(window,
			[](GLFWwindow* window)
			{
				events.OnClose(window);
			});

#pragma endregion

		glfwMakeContextCurrent(window);

		glewExperimental = true;
		if (glewInit() != GLEW_OK)
			throw std::exception("Catched error while glew initing!");
	}

	void Window::Run()
	{
		if (timer->IsRunned())
			timer->Stop();
		timer->Restart();

		while (IsOpen())
		{
			// ...
			time_current = glfwGetTime();

			// Render
			events.OnRender(time_current, time_delta);

			// Update
			glfwSwapBuffers(window);
			glfwPollEvents();
			events.OnUpdate(time_current);

			// Hearbeat
			events.OnHearbeat(time_current);

			// ...
			time_delta = time_current - time_last;
			time_last = time_current;
			inputData.currentFrame++;
		}

		terminate();
	}

	void Window::terminate() const
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		timer->Stop();
	}
}