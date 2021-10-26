#pragma once
#include "OpenGL.hpp"

namespace OpenGL
{
	template <GLenum TBufferType, typename TObject>
	class ArrayBuffer
	{
	private:
		RenderID arrayBufferObject;

	public:
		ArrayBuffer()
		{
			glGenBuffers(1, &arrayBufferObject);
		};

		ArrayBuffer(const ArrayBuffer&) = delete;

		virtual ~ArrayBuffer()
		{
			glDeleteBuffers(1, &arrayBufferObject);
		};

	public:
		virtual void Bind() const
		{
			glBindBuffer(TBufferType, arrayBufferObject);
		};

		virtual void Unbind() const
		{
			glBindBuffer(TBufferType, 0);
		};

		virtual void BufferData(GLuint size, const void* data, GLenum usage)
		{
			Bind();
			glBufferData(TBufferType, sizeof(TObject) * size, data, usage);
		}
	};
}