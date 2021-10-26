#pragma once
#include "OpenGL.hpp"

namespace OpenGL
{
	class VertexArray
	{
	private:
		RenderID vertexArrayBuffer;

	public:
		VertexArray();
		VertexArray(const VertexArray&) = delete;
		virtual ~VertexArray();

	public:
		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

		template <typename T>
		void AutoVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei offset = 1, const void* pointer = nullptr)
		{
			VertexAttribPointer(index, size, type, normalized, sizeof(T) * offset, pointer);
		};

		virtual void DisableAttrib(GLuint index);
		virtual void EnabledAttrib(GLuint index);
	};
}