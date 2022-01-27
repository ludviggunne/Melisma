#pragma once
#include "melisma/core.h"

#include "vertex_buffer_layout.h"

#include "glm/glm.hpp"

namespace melisma {

	struct Vertex {
		glm::vec3   Position;
		glm::vec2   TexCoord;
		float       TexID;
		glm::vec4   Color;
	};

	template<typename VertexType>
	VertexBufferLayout DefaultVertexBufferLayout();

	template<>
	inline VertexBufferLayout DefaultVertexBufferLayout<Vertex>() {
		VertexBufferLayout layout;

		layout.AddAttribute(VertexAttribute(AttributeType::FLOAT, 3));
		layout.AddAttribute(VertexAttribute(AttributeType::FLOAT, 2));
		layout.AddAttribute(VertexAttribute(AttributeType::FLOAT, 1));
		layout.AddAttribute(VertexAttribute(AttributeType::FLOAT, 4));

		return layout;
	}
}