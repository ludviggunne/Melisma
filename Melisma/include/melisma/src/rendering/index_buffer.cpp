#include "rendering/index_buffer.h"

#include "glcall.h"

#include "glad/glad.h"

namespace melisma {

	IndexBuffer::IndexBuffer()
	{
		GLcall(glGenBuffers(1, &m_RendererID));
	}

	IndexBuffer::~IndexBuffer()
	{
		Unbind();
		GLcall(glDeleteBuffers(1, &m_RendererID));
	}

	void IndexBuffer::Bind() const
	{
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void IndexBuffer::Unbind() const
	{
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void IndexBuffer::Data(const uint32_t *data, size_t count) const
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW); // Melisma Todo: Update to handle dynamic geometry
	}

}