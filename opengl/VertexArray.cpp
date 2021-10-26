#include "VertexArray.hpp"

namespace OpenGL
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &vertexArrayBuffer);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &vertexArrayBuffer);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(vertexArrayBuffer);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
	{
		Bind();
		EnabledAttrib(index);
		glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride, pointer);
	}

	void VertexArray::DisableAttrib(GLuint index)
	{
		glDisableVertexAttribArray(index);
	}

	void VertexArray::EnabledAttrib(GLuint index)
	{
		glEnableVertexAttribArray(index);
	}
}