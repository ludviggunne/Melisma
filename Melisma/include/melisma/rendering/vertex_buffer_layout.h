#pragma once

#include "vertex_attribute.h"

#include <vector>

namespace melisma {

	class VertexBufferLayout {
	public:
		VertexBufferLayout() : m_Stride(0) {}

		void AddAttribute(VertexAttribute attr);

		void EnableAttributes() const;

	private:
		std::vector<VertexAttribute> m_Attributes;
		unsigned int m_Stride;
	};

}