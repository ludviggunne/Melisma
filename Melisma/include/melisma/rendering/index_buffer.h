#pragma once
#include "melisma/core.h"

#include "vertex.h"

#include <cstdint>

namespace melisma {

	class melismaAPI IndexBuffer {
	public:
		IndexBuffer();
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		void Data(const uint32_t *data, size_t count) const;

	private:
		unsigned int m_RendererID;
	};

}