#pragma once

#include "vertex.h"

namespace melisma {

	class VertexBuffer {
	public:
		VertexBuffer();
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void Data(const Vertex *data, size_t count) const;

	private:
		unsigned int m_RendererID;
	};

}