#include "melisma/rendering/vertex_array_object.h"

#include "glad/glad.h"

#include "glcall.h"

namespace melisma {

	VertexArrayObject::VertexArrayObject(const VertexBufferLayout &layout)
	{
		GLcall(glGenVertexArrays(1, &m_RendererID));

		Bind();
		layout.EnableAttributes();
		Unbind();
	}

	VertexArrayObject::~VertexArrayObject()
	{
		GLcall(glDeleteVertexArrays(1, &m_RendererID));
	}

	void VertexArrayObject::VertexData(const Vertex *data, size_t size) const
	{
		m_vertexBuffer.Data(data, size);
	}

	void VertexArrayObject::IndexData(const uint32_t *data, size_t size) const
	{
		m_indexBuffer.Data(data, size);
	}

	void VertexArrayObject::Bind() const
	{
		GLcall(glBindVertexArray(m_RendererID));

		m_vertexBuffer.Bind();
		m_indexBuffer.Bind();
	}

	void VertexArrayObject::Unbind() const
	{
		GLcall(glBindVertexArray(0));

		m_vertexBuffer.Unbind();
		m_indexBuffer.Unbind();
	}

	void VertexArrayObject::Draw(Primitive primitive, size_t indices) const
	{
		GLcall(glDrawElements((GLenum)primitive, indices, GL_UNSIGNED_INT, 0));
	}

}