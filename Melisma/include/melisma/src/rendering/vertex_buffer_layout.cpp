#include "rendering/vertex_buffer_layout.h"

#include "glad/glad.h"

#include "glcall.h"

namespace melisma {

	void VertexBufferLayout::AddAttribute(VertexAttribute attr)
	{
		m_Attributes.push_back(attr);
		m_Stride += attr.m_TypeSize * attr.Size;
	}

	void VertexBufferLayout::EnableAttributes() const
	{
		size_t offset = 0;
		unsigned int index  = 0;
		for (auto &attr : m_Attributes) {
			GLcall(glVertexAttribPointer(index, attr.Size, (GLenum)attr.Type, GL_FALSE, m_Stride, (const void *)offset));
			GLcall(glEnableVertexAttribArray(index));

			offset += attr.m_TypeSize * attr.Size;
			index++;
		}
	}

}
