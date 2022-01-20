#pragma once
#include "melisma/core.h"

#include "vertex.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"

namespace melisma {

	enum class Primitive {
		Triangles = 0x0004,
		Lines = 0x0001
	};

	class VertexArrayObject {
	public:
		VertexArrayObject(const VertexBufferLayout& layout);
		~VertexArrayObject();

		void VertexData(const Vertex *data, size_t size) const;
		void IndexData(const uint32_t *data, size_t size) const;

		void Bind() const;
		void Unbind() const;

		void Draw(Primitive primitive, size_t indices) const;

	private:
		unsigned int m_RendererID;

		VertexBuffer m_vertexBuffer;
		IndexBuffer m_indexBuffer;
	};

}