#include "melisma/rendering/vertex_buffer.h"

#include "glcall.h"

#include "glad/glad.h"

namespace melisma {

	VertexBuffer::VertexBuffer()
	{
		GLcall(glGenBuffers(1, &m_RendererID));
	}

	VertexBuffer::~VertexBuffer()
	{
		Unbind();
		GLcall(glDeleteBuffers(1, &m_RendererID));
	}

	void VertexBuffer::Bind() const
	{
		GLcall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void VertexBuffer::Unbind() const
	{
		GLcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::Data(const Vertex *data, size_t count) const
	{
		GLcall(glBufferData(GL_ARRAY_BUFFER, count, data, GL_STATIC_DRAW)); // Melisma Todo: Update to handle dynamic geometry
	}

}
