#pragma once
#include <GL/glew.h>
#include "utils/graphics/Color.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

namespace OpenGL
{
	typedef GLuint RenderID;
	typedef GLuint BufferID;

	inline void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	inline bool GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			std::cout << "[OpenGL Error]: (" << error << "): " <<
				function << " " << file << ":" << line << std::endl;
			std::cout << "[OpenGL Error]: Error Name \"" << glewGetErrorString(error) << "\"" << std::endl;
			return false;
		}
		return true;
	}

	inline void ClearColor(const graphics::Color3& c)
	{
		glClearColor(c.R / 255.f, c.G / 255.f, c.B / 255.f, 1.0);
	}

	inline void ClearColorBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	inline void ClearDepthBuffer()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	inline void ClearStencilBuffer()
	{
		glClear(GL_STENCIL_BUFFER_BIT);
	}
}